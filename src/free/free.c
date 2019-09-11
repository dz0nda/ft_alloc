# include "free.h"

void    ft_free(void *ptr)
{
    t_anode *node;
    FT_ALLOC_UINT addr;
    
    node = NULL;
    addr = (FT_ALLOC_UINT)ptr;
    if (ptr == NULL || addr == 0)
        return ;
    if ((node = ft_alloc_search_by_address(addr)) == NULL)
            return ;
    ft_alloc_info_used_free(node->size, TRUE);
    ft_alloc_concat(node);
    node->free = TRUE;
}