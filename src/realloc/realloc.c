# include "realloc.h"

static int   ft_realloc_by_consolidate(t_aarena *arena, void *ptr, size_t size)
{
  t_achunk   *node;
  t_aindex   new_idx;
  t_aindex   node_idx;

  node = NULL;
  new_idx = ft_alloc_get_arena_index_by_size_request(size);
  node_idx = ft_alloc_get_arena_index_by_size_arena(arena->size);
  if ((new_idx != node_idx) || ((node = ft_alloc_search_chunk_by_address(arena, ptr)) == NULL))
    return (EXIT_FAILURE);
  if (size > node->size)
  {
    ft_alloc_chunk_concat(arena, node);
    ptr = (void *)(node + 1);
  }
  ft_alloc_chunk_split(arena, node, size);
  ft_alloc_chunk_concat(arena, node->next);
  if (size > node->size)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static void *ft_realloc_by_mmap(void *ptr, size_t size)
{
    void    *new;

    if ((new = ft_malloc(size)) == NULL)
      return (NULL);
    ft_memcpy(new, ptr, size);
    ft_free(ptr);
    return (new);
}

void    *ft_realloc(void *ptr, size_t size)
{
  t_aarena *arena;
  void *new;

  arena = NULL;
  new = NULL;
  size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
  if (ptr == NULL)
    return (ft_malloc(size));
  if ((arena = ft_alloc_search_arena_by_address(ptr)) == NULL)
    return (ptr);
  if ((ft_realloc_by_consolidate(arena, ptr, size)) == EXIT_SUCCESS)
    return (ptr);
  return (ft_realloc_by_mmap(ptr, size));
}