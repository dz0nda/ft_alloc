# include "alloc.h"

static t_achunk   *ft_alloc_search_first_fit(t_achunk *head, size_t size)
{
    t_achunk  *node;

    node = NULL;
    if ((node = head) == NULL)
        return (NULL);
    while (node->next != head)
    {
        if (node->size >= size && node->free == TRUE)
            break;
        node = node->next;
    }
    if (node->size >= size && node->free == TRUE)
        return (node);
    return (NULL);
}

static int     ft_alloc_is_in_arena(t_aarena *arena, void *ptr)
{
    FT_ALLOC_UINT addr_arena;
    FT_ALLOC_UINT addr_ptr;

    addr_arena = (FT_ALLOC_UINT)arena;
    addr_ptr = (FT_ALLOC_UINT)ptr;
    if ((addr_arena + FT_ALLOC_SIZE_ARENA) <= addr_ptr && addr_ptr <= (addr_arena + arena->size))
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

static int     ft_alloc_is_in_chunk(t_achunk *node, void *ptr)
{
    FT_ALLOC_UINT adrr_chunk;
    FT_ALLOC_UINT addr_ptr;

    adrr_chunk = (FT_ALLOC_UINT)node;
    addr_ptr = (FT_ALLOC_UINT)ptr;
    if ((adrr_chunk + FT_ALLOC_SIZE_CHUNK) <= addr_ptr && addr_ptr <= (adrr_chunk + node->size))
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

t_aarena    **ft_alloc_search_arena_by_address(void *ptr)
{
    t_aindex index;
    t_aarena **arena;
    
    index = -1;
    arena = NULL;
    while (++index < ALLOC_NONE)
    {
        arena = &(g_alloc_state.alloc_arena)[index];
        while (*arena)
        {
            if (ft_alloc_is_in_arena(*arena, ptr) == EXIT_SUCCESS)
                return (arena);
            *arena = (*arena)->next;
        }
    }
    return (NULL);
}

t_achunk    *ft_alloc_search_chunk_by_address(t_aarena *arena, void *ptr)
{
    t_achunk *node;

    if (arena == NULL)
        return (NULL);
    node = arena->head;
    if (node->free == FALSE && ft_alloc_is_in_chunk(node, ptr) == EXIT_SUCCESS)
        return (node);
    while((node = node->next) != arena->head && node->free == FALSE)
    {
        if (ft_alloc_is_in_chunk(node, ptr) == EXIT_SUCCESS)
            return (node);
        node = node->next;
    }
    return (NULL);
}

t_achunk          *ft_alloc_search_chunk_by_size(t_aarena *arena, size_t size)
{
    t_achunk *node;

    node = NULL;
    while (arena && (node = ft_alloc_search_first_fit(arena->head, size)) == NULL)
        arena = arena->next;
    return (node);
}