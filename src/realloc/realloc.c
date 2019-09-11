# include "realloc.h"

t_anode     *ft_realloc_fast(t_anode *node, size_t size)
{
  t_anode   *new;
  t_aarena   node_idx;
  t_aarena   new_idx;

  new = node;
  node_idx = ft_alloc_get_arena_index_by_size(node->size);
  new_idx = ft_alloc_get_arena_index_by_size(size);

    if (ft_alloc_get_arena_index_by_size(node->size) != 
    ft_alloc_get_arena_index_by_size(size))
      return (NULL);
    if (size < node->size)
      if (ft_alloc_split(node, size) == EXIT_SUCCESS)
        return (node);
    else if (node->next->free == TRUE)
      ; //concat right
    else if (node->prev->free == TRUE)
      ;
    return (NULL);
}

t_anode     *ft_realloc_get_fast(t_anode *node, size_t size)
{
  t_anode   *new;
  t_aarena   node_idx;
  t_aarena   new_idx;

  new = node;
  node_idx = ft_alloc_get_arena_index_by_size(node->size);
  new_idx = ft_alloc_get_arena_index_by_size(size);
  if (node_idx != new_idx)
    return (NULL);
  if (ft_alloc_split(new, size) == EXIT_SUCCESS)
    return (new);
  return (NULL);
  // else
  // {
  //   if (node->next->free == TRUE && (node->size + node->next->size) > size)

  // }
  //   if (ft_alloc_concat(node))
  
  //   else if (node->next->free == TRUE)
  //     ; //concat right
  //   else if (node->prev->free == TRUE)
  //     ;
  //   return (NULL);
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
    if (ptr == NULL || addr == 0)
      return (ft_malloc(size));
    else if (size == 0)
      ft_free(ptr);
    else if ((node = ft_alloc_search_by_address(addr)) == NULL)
      return (ptr);
    if ((new = ft_realloc_get_fast(node, size)) == NULL)
      return (NULL);


    return (NULL);

  //   if (size == node->size || (node->size > size && node->size - size < FT_ALLOC_ALIGNMENT))
  //     return (ptr);
  //   if ((new = ft_realloc_fast(node, size)) == NULL)
  //     if ((new = ft_malloc(size)) == NULL)
  //       return (NULL);
  // return (ptr);
}