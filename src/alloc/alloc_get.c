#include "alloc.h"

t_aarena  **ft_alloc_get_arena_by_size_request(size_t size)
{
  t_ainfo info;
  t_astate  *state;

  info = g_alloc.info;
  state = &(g_alloc).state;
  if (size <= info.tiny_size_request)
      return (&(state->arena)[ALLOC_TINY]);
  else if (size > info.tiny_size_request && size <= info.small_size_request)
    return (&(state->arena)[ALLOC_SMALL]);
  return (&(state->arena)[ALLOC_LARGE]);
}

t_aindex  ft_alloc_get_arena_index_by_size_request(size_t size)
{
  t_ainfo info;

  info = g_alloc.info;
  if (size <= info.tiny_size_request)
    return (ALLOC_TINY);
  else if (size > info.tiny_size_request && size <= info.small_size_request)
    return (ALLOC_SMALL);
  return (ALLOC_LARGE);
}

size_t    ft_alloc_get_arena_size_by_size_request(size_t size)
{
  t_ainfo info;

  info = g_alloc.info;
  if (size <= info.tiny_size_request)
    return (info.tiny_size_arena);
  else if (size > info.tiny_size_request && size <= info.small_size_request)
    return (info.small_size_arena);
  return (ft_alloc_get_size_aligned((size + info.size_arena), info.pagesize));
}

size_t 	  ft_alloc_get_size_aligned(size_t offset, size_t align)
{
	return ((offset % align == 0) ? offset : offset + (align - (offset % align) % align));
}