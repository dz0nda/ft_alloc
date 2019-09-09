# include "free.h"

// void    ft_alloc_merge_node(t_node *node)
// {
//     if (node->next && node->next->free == TRUE)
//     {
//         node->size += node->next->size;
//         node->next = node->next->next;
//     }
// }

// void    ft_alloc_total_prune(size_t size)
// {
//     e_alloc_arena arena_size;
//     size_t arena_size_map;

//     arena_size = ALLOC_NONE;
//     arena_size_map = 0;
//     arena_size = ft_alloc_getsize_arena(size);
//     arena_size_map = ft_alloc_getsize_map(size);
//     if (g_allocinfo.total_allocated[arena_size] == 0)
//         munmap(g_allocinfo.arena[arena_size], arena_size_map);
// }

int     ft_alloc_is_alloc(t_anode *node, FT_ALLOC_UINT ptr)
{
    FT_ALLOC_UINT addr;

    addr = (FT_ALLOC_UINT)node;
    printf("Addr = %ld\n", addr);
    // if (addr < ptr && ptr < addr + node->size)
    if ((addr + FT_ALLOC_SIZE_NODE) == ptr)
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

t_anode    *ft_alloc_search_address(FT_ALLOC_UINT ptr)
{
    t_aarena arena;
    t_anode *head;
    t_anode *node;
    size_t size;

    arena = -1;
    head = NULL;
    node = NULL;
    size = 0;
    printf("PTR = %ld \n", ptr);
    while (++arena < ALLOC_NONE)
    {
        head = g_alloc_state.alloc_arena[arena];
        node = head;
        while((node = node->next) != head && node->free == FALSE)
            if (ft_alloc_is_alloc(node, ptr) == EXIT_SUCCESS)
                return (node);
        if (ft_alloc_is_alloc(node, ptr) == EXIT_SUCCESS)
            return (node);
    }
    return (NULL);
}

void    ft_free(void *ptr)
{
    t_anode *node;

    FT_ALLOC_UINT size = (FT_ALLOC_UINT)ptr;
    printf("size = %ld \n", size);

    if ((node = ft_alloc_search_address((FT_ALLOC_UINT)ptr)) == NULL)
    {
        printf("here in free");
            return ;
    }
    node->free = TRUE;
    // t_node *node;

    // node = NULL;
    // node = (t_node *)((FT_ALLOC_PTR_UINT)ptr - sizeof(t_node));
    // if (node->free != TRUE && node->free != FALSE)
    //     return ;
    // node->free = TRUE;
    // ft_alloc_update_total(node->size, node->free);
    // ft_alloc_merge_node(node);
    // ft_alloc_total_prune(node->size);
}