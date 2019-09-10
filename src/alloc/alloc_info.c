#include "alloc.h"

int   ft_alloc_info_mmap(size_t size, t_bool free)
{
  t_alloc_info *info;
  t_aarena index;
	size_t	size_arena;

  info = &(g_alloc_state).alloc_info;
  index = ft_alloc_get_arena_index_by_size(size);
	size_arena = ft_alloc_get_arena_size_by_size(size);
  if (free == TRUE)
  {
    if (info->a_mmap < size_arena || info->a_free[index] < size_arena)
      return (ft_alloc_error(AE_a_mmap));
    info->a_mmap -= size_arena;
    info->a_free[index] -= (size_arena - FT_ALLOC_SIZE_META);
  }
  else if (free == FALSE)
  {
    if ((info->a_mmap + size_arena) > info->rlim_cur)
      return (ft_alloc_error(AE_a_mmap));
    info->a_mmap += size_arena;
    info->a_free[index] += (size_arena - FT_ALLOC_SIZE_META);
  }
  return (EXIT_SUCCESS);
}

int   ft_alloc_info_used_free(size_t size, t_bool free)
{
  t_alloc_info *info;
  t_aarena index;

  info = &(g_alloc_state).alloc_info;
  index = ft_alloc_get_arena_index_by_size(size + FT_ALLOC_SIZE_META);    
  if (free == TRUE)
  {
    info->a_used[index] -= size;
    info->a_free[index] += size;
  }
  else if (free == FALSE)
  {
    info->a_used[index] += size;
    info->a_free[index] -= size;
  }
  else
    return (ft_alloc_error(AE_RALL));
  return (EXIT_SUCCESS);
}

int   ft_alloc_info_free(size_t size, t_bool free)
{
    t_alloc_info *info;
    t_aarena index;

    info = &(g_alloc_state).alloc_info;
    index = ft_alloc_get_arena_index_by_size(size + FT_ALLOC_SIZE_META);
    if (free == TRUE)
      info->a_free[index] += FT_ALLOC_SIZE_META;
    else if (free == FALSE)
      info->a_free[index] -= FT_ALLOC_SIZE_META;
    else
      return (ft_alloc_error(AE_RALL));
    return (EXIT_SUCCESS);
}


int   ft_alloc_info_address(FT_ALLOC_UINT ptr, size_t size)
{
  t_alloc_info *info;
  t_aarena index;

  info = &(g_alloc_state).alloc_info;
  index = ft_alloc_get_arena_index_by_size(size);
  info->a_addr[index] = ptr;
  return (EXIT_SUCCESS);
}