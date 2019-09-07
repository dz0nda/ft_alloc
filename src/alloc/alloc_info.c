#include "alloc.h"

int   ft_ainfo_mmap(t_aarena arena, size_t size, t_bool free)
{
  t_alloc_info *info;

  info = &(g_alloc_state).alloc_info;
  if (free == TRUE)
  {
    if (info->rall_mmap < size || info->rall_freed[arena] < size)
      return (ft_alloc_error(AE_RALL_MMAP));
    info->rall_mmap -= size;
    info->rall_freed[arena] -= size;
  }
  else if (free == FALSE)
  {
    if ((info->rall_mmap + size) > info->rlim_cur)
      return (ft_alloc_error(AE_RALL_MMAP));
    info->rall_mmap += size;
    info->rall_freed[arena] += size;
  }
  return (EXIT_SUCCESS);
}

int   ft_ainfo_rall(t_aarena arena, size_t size, t_bool free)
{
  t_alloc_info *info;

  info = &(g_alloc_state).alloc_info;
  if (free == TRUE)
  {
    info->rall_inuse[arena] -= size;
    info->rall_freed[arena] += size;
  }
  else if (free == FALSE)
  {
    info->rall_inuse[arena] += size;
    info->rall_freed[arena] -= size;
  }
  else
    return (ft_alloc_error(AE_RALL));
  return (EXIT_SUCCESS);
}

int   ft_ainfo_raddr(t_aarena arena, FT_ALLOC_UINT ptr)
{
  t_alloc_info *info;

  info = &(g_alloc_state).alloc_info;
  info->raddr[arena] = ptr;
  return (EXIT_SUCCESS);
}