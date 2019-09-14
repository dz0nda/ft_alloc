#include "alloc.h"

int   ft_alloc_info_freed(t_aarena *arena, size_t size, t_bool free)
{
  t_aindex aindex;
  t_ainfo  *info;

  aindex = arena->aindex;
  info = &(g_alloc_state).alloc_info;
  if (free == TRUE)
    info->a_freed[aindex] += size;
  else
    info->a_freed[aindex] -= size;
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

int   ft_alloc_info_total(t_aarena *arena, size_t size, t_bool free)
{
  t_aindex aindex;
  t_ainfo  *info;

  aindex = arena->aindex;
  info = &(g_alloc_state).alloc_info;
  if (free == TRUE)
  {
    info->a_freed[aindex] += size;
    info->a_used[aindex] -= size;
  }
  else
  {
    info->a_freed[aindex] -= size;
    info->a_used[aindex] += size;
  }
  return (EXIT_SUCCESS);
}

int   ft_alloc_info_used(t_aarena *arena, size_t size, t_bool free)
{
  t_aindex aindex;
  t_ainfo  *info;

  aindex = arena->aindex;
  info = &(g_alloc_state).alloc_info;
  if (free == TRUE)
    info->a_used[aindex] -= size;
  else
    info->a_used[aindex] += size;
  return (EXIT_SUCCESS);
}