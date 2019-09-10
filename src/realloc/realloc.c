# include "realloc.h"

t_anode     *ft_realloc_fast(t_anode *node, size_t size)
{
  t_anode   *new;

    new = node;
    if (ft_alloc_get_arena_index_by_size(node->size) != 
    ft_alloc_get_arena_index_by_size(size))
      return (NULL);
    if (size < node->size)
      if (ft_alloc_arena_split(node, size) == EXIT_SUCCESS)
        return (node);
    else if (node->next->free == TRUE)
      ; //concat right
    else if (node->prev->free == TRUE)
      ;
    return (NULL);
}

void    *ft_realloc(void *ptr, size_t size)
{
    t_anode *node;
    t_anode *new;
    FT_ALLOC_UINT addr;

    node = NULL;
    new = NULL;
    addr = (FT_ALLOC_UINT)ptr;
    size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
    if (size == 0)
      return (NULL);
    if (ptr == NULL || addr == 0)
        return (ptr = ft_malloc(size));
    if ((node = ft_alloc_search_node_by_address(addr)) == NULL)
        return (NULL);
    if (size == node->size || (node->size > size && node->size - size < FT_ALLOC_ALIGNMENT))
      return (ptr);
    if ((new = ft_realloc_fast(node, size)) == NULL)
      if ((new = ft_malloc(size)) == NULL)
        return (NULL);

  return (ptr);
}