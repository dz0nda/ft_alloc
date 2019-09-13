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

int         ft_realloc_get_fast(void *ptr, size_t size, t_anode *node)
{
  t_anode   *new;
  t_aarena   new_idx;
  t_aarena   node_idx;

  new = node;
  new_idx = ft_alloc_get_arena_index_by_size(size);
  node_idx = ft_alloc_get_arena_index_by_size(node->size);
  if (node_idx != new_idx)
    return (EXIT_FAILURE);
  if (size <= node->size)
  {
    if (ft_alloc_split(new, size) == EXIT_FAILURE)
      return (EXIT_SUCCESS);
    ft_alloc_concat_next(new->next);
  }

  if (node->next->free == TRUE && (node->next->size + node->size) >= size)
    if (ft_alloc_concat_next(node) == EXIT_FAILURE)
      return (EXIT_FAILURE);
  ft_alloc_split(node, size);
  return (EXIT_SUCCESS);
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

    node = NULL;
    new = NULL;
    size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
    if (ptr == NULL)
      return (ft_malloc(size));
    else if (size == 0)
      ft_free(ptr);
    else if ((node = ft_alloc_search_by_address(ptr)) == NULL)
      return (ptr);
    if ((ft_realloc_get_fast(ptr, size, node)) == EXIT_SUCCESS)
      return (ptr);
    return (NULL);

  //   if (size == node->size || (node->size > size && node->size - size < FT_ALLOC_ALIGNMENT))
  //     return (ptr);
  //   if ((new = ft_realloc_fast(node, size)) == NULL)
  //     if ((new = ft_malloc(size)) == NULL)
  //       return (NULL);
  // return (ptr);
}