#include "alloc.h"

int   ft_ainfo_rall(t_alloc_arena arena, size_t size, t_bool free)
{
  t_alloc_info *info;

  info = &(g_alloc_state).alloc_info;
  if (arena == ALLOC_NONE)
  {
    if (free = TRUE && info->rall_mmap >= size)
      info->rall_mmap -= size;
    else if (free == FALSE && (info->rall_mmap + size) <= info->rlim_cur)
      info->rall_mmap += size;
    else
      return (ft_alloc_error(AE_RALL_MMAP));
  }
  else if (free == TRUE && info->rall_inuse[arena] >= size)
  {
    info->rall_inuse[arena] -= size;
    info->rall_freed[arena] += size;
  }
  else if (free == FALSE && info->rall_freed[arena] >= size)
  {
    info->rall_inuse[arena] += size;
    info->rall_freed[arena] -= size;
  }
  else
    return (ft_alloc_error(AE_RALL));
  return (EXIT_SUCCESS);
}