#include "alloc.h"

t_aarena  **ft_alloc_get_arena_by_size(size_t size)
{
  if (size <= FT_ALLOC_TINY)
    return (&(g_alloc_state.alloc_arena)[ALLOC_TINY]);
  else if (size > FT_ALLOC_TINY && size <= FT_ALLOC_SMALL)
    return (&(g_alloc_state.alloc_arena)[ALLOC_SMALL]);
  return (&(g_alloc_state.alloc_arena)[ALLOC_LARGE]);
}

t_aindex  ft_alloc_get_arena_index_by_size_arena(size_t size)
{
  if (size == FT_ALLOC_N)
    return (ALLOC_TINY);
  else if (size == FT_ALLOC_M)
    return (ALLOC_SMALL);
  return (ALLOC_LARGE);
}

t_aindex  ft_alloc_get_arena_index_by_size_request(size_t size)
{
  if (size <= FT_ALLOC_TINY)
    return (ALLOC_TINY);
  else if (size > FT_ALLOC_TINY && size <= FT_ALLOC_SMALL)
    return (ALLOC_SMALL);
  return (ALLOC_LARGE);
}

size_t    ft_alloc_get_arena_size_by_size_request(size_t size)
{
  if (size <= FT_ALLOC_TINY)
    return (FT_ALLOC_N);
  else if (size > FT_ALLOC_TINY && size <= FT_ALLOC_SMALL)
    return (FT_ALLOC_M);
  return (ft_alloc_get_size_aligned(size, FT_ALLOC_PAGESIZE));
}

size_t 	  ft_alloc_get_size_aligned(size_t offset, size_t align)
{
	return (offset + (align - (offset % align) % align));
}