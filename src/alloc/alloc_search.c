# include "alloc.h"

static t_anode   *ft_alloc_search_first_fit(t_anode *head, size_t size)
{
    t_anode  *node;

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

static int     ft_alloc_is_alloc(t_anode *node, FT_ALLOC_UINT ptr)
{
    FT_ALLOC_UINT addr;

    addr = (FT_ALLOC_UINT)node;
    // if (addr < ptr && ptr < addr + node->size)
    if ((addr + FT_ALLOC_SIZE_NODE) == ptr)
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

t_anode          *ft_alloc_search(t_anode **head, size_t size)
{
    t_anode *node;

    node = NULL;
    if (*head == NULL)
        return (NULL);
    if ((node = ft_alloc_search_first_fit(*head, size)) == NULL)
        return (NULL);
    return (node);
}

t_anode          *ft_alloc_search_node_by_size(size_t size)
{
    t_anode *head;
    t_anode *node;
    t_aarena arena;

    head = NULL;
    node = NULL;
    arena = ft_alloc_get_arena_index_by_size(size);
    if ((head = g_alloc_state.alloc_arena[arena]) == NULL)
        return (NULL);
    if ((node = ft_alloc_search_first_fit(head, size)) == NULL)
        return (NULL);
    return (node);
}

t_anode    *ft_alloc_search_node_by_address(FT_ALLOC_UINT address)
{
    t_aarena arena;
    t_anode *head;
    t_anode *node;

    arena = -1;
    head = NULL;
    node = NULL;
    while (++arena < ALLOC_NONE)
    {
        head = g_alloc_state.alloc_arena[arena];
        node = head;
        while(node != head && node->free == FALSE)
        {
            if (ft_alloc_is_alloc(node, address) == EXIT_SUCCESS)
                return (node);
            node = node->next;
        }
        if (node->free == FALSE && ft_alloc_is_alloc(node, address) == EXIT_SUCCESS)
            return (node);
    }
    return (NULL);
}