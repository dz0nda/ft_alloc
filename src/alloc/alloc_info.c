#include "alloc.h"

int   ft_alloc_info_total(t_aarena *arena, size_t size, t_bool free)
{
  t_aindex index;
  t_ainfo  *info;

  if ((index = ft_alloc_get_arena_index_by_size_arena(arena->size)) == ALLOC_NONE)
    return (EXIT_FAILURE);
  info = &(g_alloc_state).alloc_info;
  if (free == TRUE)
  {
    info->a_freed[index] += size;
    info->a_used[index] -= size;
  }
  else
  {
    info->a_freed[index] -= size;
    info->a_used[index] += size;
  }
  return (EXIT_SUCCESS);
}

int   ft_alloc_info_freed(t_aarena *arena, size_t size, t_bool free)
{
  t_aindex index;
  t_ainfo  *info;

  if ((index = ft_alloc_get_arena_index_by_size_arena(arena->size)) == ALLOC_NONE)
    return (EXIT_FAILURE);
  ft_putnbr(index);
  info = &(g_alloc_state).alloc_info;
  if (free == TRUE)
    info->a_freed[index] += size;
  else
    info->a_freed[index] -= size;
  return (EXIT_SUCCESS);
}

int   ft_alloc_info_mmap(size_t size, t_bool mmap)
{
  t_ainfo *info;

  info = &(g_alloc_state).alloc_info;
  if (mmap == TRUE)
    info->a_mmap += size;
  else
    info->a_mmap -= size;
  return (EXIT_SUCCESS);
}

int   ft_alloc_info_used(t_aarena *arena, size_t size, t_bool free)
{
  t_aindex index;
  t_ainfo  *info;

  if ((index = ft_alloc_get_arena_index_by_size_arena(arena->size)) == ALLOC_NONE)
    return (EXIT_FAILURE);
  info = &(g_alloc_state).alloc_info;
  if (free == TRUE)
    info->a_used[index] -= size;
  else
    info->a_used[index] += size;
  return (EXIT_SUCCESS);
}