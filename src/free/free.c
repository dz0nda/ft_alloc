# include "free.h"

void    ft_free(void *ptr)
{
    t_anode *node;
    
    node = NULL;
    if (ptr == NULL)
        return ;
    if ((node = ft_alloc_search_by_address(ptr)) == NULL)
        return ;
    ft_alloc_info_used_free(node->size, TRUE);
    ft_alloc_concat(node);
    node->free = TRUE;
}