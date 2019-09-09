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


int     ft_alloc_is_concat(t_anode *node)
{
    FT_ALLOC_UINT addr_prev;
    FT_ALLOC_UINT addr_next;

    addr_prev = (FT_ALLOC_UINT)node->prev;
    addr_next = (FT_ALLOC_UINT)node->next;
    if ((node->prev < node) && (node->prev->free == TRUE))
    {
        node->prev->size += node->size + FT_ALLOC_SIZE_NODE;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node = node->prev;
    }
    if ((node->next > node) && (node->next->free == TRUE))
    {
        node->size += node->next->size + FT_ALLOC_SIZE_NODE;
        node->next = node->next->next;
        node->next->prev = node;
    }
    return (EXIT_SUCCESS);
}

void    ft_free(void *ptr)
{
    FT_ALLOC_UINT addr;
    t_anode *node;
    
    addr = (FT_ALLOC_UINT)ptr;
    if (ptr == NULL || addr == 0)
        return ;
    if ((node = ft_alloc_search_node_by_address(addr)) == NULL)
            return ;
    ft_alloc_is_concat(node);
    node->free = TRUE;

    // ft_alloc_update_total(node->size, node->free);
    // ft_alloc_merge_node(node);
    // ft_alloc_total_prune(node->size);
}