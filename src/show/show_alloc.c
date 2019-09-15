#include "show.h"

static void  ft_show_alloc_detail(const char *s, FT_ALLOC_UINT nb)
{
  ft_putstr(s);
  ft_putnbr(nb);
  ft_putstr("\n");
}

void      ft_show_alloc_info(void)
{
  t_ainfo info;

  info = g_alloc.info;
  ft_putstr("\n========================= Alloc Info =========================\n");
  ft_show_alloc_detail("\nSoft limit max allocated bytes : ", info.rlim_cur);
  ft_show_alloc_detail("Hard limit max allocated bytes : ", info.rlim_max);
  ft_show_alloc_detail("Pagesize : ", info.pagesize);
  ft_show_alloc_detail("Tiny size request : ", info.tiny_size_request);
  ft_show_alloc_detail("Small size request : ", info.small_size_request);
  ft_show_alloc_detail("Tiny size arena : ", info.tiny_size_arena);
  ft_show_alloc_detail("Small size arena : ", info.small_size_arena);
}


void  ft_show_alloc_state(void)
{
  t_aindex i;
  t_astate state;
	const char *aindex[ALLOC_NONE] = { "TINY", "SMALL", "LARGE" };

  i = ALLOC_TINY;
  state = g_alloc.state;
  ft_putstr("\n========================= Alloc State =========================\n");
  while (i < ALLOC_NONE)
  {
      ft_putstr("\nArena [ ");
      ft_putstr(aindex[i]);
      ft_putstr(" ] \n");
      ft_show_alloc_detail("Total mmaped in bytes : ", state.mmap[i]);
      ft_show_alloc_detail("Total used in bytes : ", state.used[i]);
      ft_show_alloc_detail("Total freed in bytes : ", state.freed[i]);
      ft_putstr("Addresses : \n");
      ft_show_alloc_arena(g_alloc.state.arena[i], -1);
      i++;
	}
}