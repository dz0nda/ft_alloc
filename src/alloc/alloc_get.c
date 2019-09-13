#include "alloc.h"

size_t	ft_alloc_get_size_aligned(size_t offset, size_t align)
{
	return (offset + (align - (offset % align) % align));
}


t_aarena  ft_alloc_get_arena_index_by_size(size_t size)
{
  if (size <= FT_ALLOC_TINY)
    return (ALLOC_TINY);
  else if (size > FT_ALLOC_TINY && size <= FT_ALLOC_SMALL)
    return (ALLOC_SMALL);
  return (ALLOC_LARGE);
}

size_t  ft_alloc_get_arena_size_by_size(size_t size)
{
  if (size <= FT_ALLOC_TINY)
    return (FT_ALLOC_N);
  else if (size > FT_ALLOC_TINY && size <= FT_ALLOC_SMALL)
    return (FT_ALLOC_M);
  return (ft_alloc_get_size_aligned(size, FT_ALLOC_PAGESIZE));
}

t_anode  **ft_alloc_get_arena_by_size(size_t size)
{
  if (size <= FT_ALLOC_TINY)
    return (&(g_alloc_state.alloc_arena)[ALLOC_TINY]);
  else if (size > FT_ALLOC_TINY && size <= FT_ALLOC_SMALL)
    return (&(g_alloc_state.alloc_arena)[ALLOC_SMALL]);
  return (&(g_alloc_state.alloc_arena)[ALLOC_LARGE]);
}