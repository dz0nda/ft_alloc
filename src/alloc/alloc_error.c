#include "alloc.h"

int ft_alloc_error(t_aerror err)
{
  ft_putstr("ft_alloc has exited with error : ");
  if (err == AE_RALL)
    ft_putstr("AE_RALL_MMAP \n");
  if (err == AE_RALL_MMAP)
    ft_putstr("AE_RALL_MMAP \n");
  if (err == AE_UNDEFINED)
    ft_putstr("AE_UNDEFINED \n");
  exit (EXIT_FAILURE);
}