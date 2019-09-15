# include "free.h"

void    ft_free(void *ptr)
{
    t_aarena **arena;
    t_achunk *node;
    
    arena = NULL;
    node = NULL;
    if ((ptr == NULL) || ((arena = ft_alloc_search_arena_by_address(ptr)) == NULL))
        return ; 
    if ((node = ft_alloc_search_chunk_by_address(*arena, ptr)) == NULL)
        return ;
    node->free = TRUE;
    ft_alloc_state_swap((*arena)->aindex, node->size, TRUE);
    ft_alloc_chunk_concat(*arena, node);
    if ((*arena)->head == node && 
    (g_alloc.info.size_arena + node->size) == (*arena)->size)
         ft_alloc_arena_del(arena);
}