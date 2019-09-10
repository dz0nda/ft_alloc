#include "show.h"

void  ft_show_alloc_info(void)
{
  t_aarena arena;
  t_alloc_info *alloc_info;

  arena = ALLOC_TINY;
  alloc_info = NULL;
  alloc_info = &(g_alloc_state).alloc_info;
  ft_putstr("== Alloc Infos ==");
  ft_putstr("\nSoft limit max allocated bytes : ");
  ft_putnbr(alloc_info->rlim_cur);
  ft_putstr("\nHard limit max allocated bytes : ");
  ft_putnbr(alloc_info->rlim_max);
  ft_putstr("\nTotal mmap requested bytes : ");
  ft_putnbr(alloc_info->a_mmap);
  while (arena < ALLOC_NONE)
  {
    ft_putstr("\nArena ");
    ft_putnbr(arena);
    ft_putstr(" : \nTotal in use bytes : ");
    ft_putnbr(alloc_info->a_used[arena]);
    ft_putstr("\nTotal free bytes : ");
    ft_putnbr(alloc_info->a_free[arena]);
    ft_putstr("\nAdress of begin section : ");
    ft_show_address(alloc_info->a_addr[arena], 0);
    arena++;
  }
  ft_putchar('\n');
}