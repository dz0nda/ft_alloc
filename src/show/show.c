# include "show.h"

static void ft_show_alloc(t_bool details)
{
	const char *aindex[ALLOC_NONE] = { "[ TINY ] ", "[ SMALL ] ", "[ LARGE ] " };
  t_aindex i;
  t_astate state;
	t_aarena *arena;

	i = -1;
  state = g_alloc.state;
	ft_putstr("show_alloc_mem : \n\n");
	while (++i < ALLOC_NONE)
	{
		ft_putstr(aindex[i]);
		ft_show_alloc_detail("- used : ", state.used[i], FALSE);
		ft_show_alloc_detail("- freed : ", state.freed[i], FALSE);
		ft_show_alloc_detail("- overhead : ", state.ovhead[i], TRUE);
		if ((arena = state.arena[i]) != NULL)
			while (arena)
			{
				ft_putstr(" - ");
				ft_show_alloc_addr((FT_ALLOC_UINT)arena->head, arena->size - g_alloc.info.size_arena, -1);
				if (details)
					ft_show_alloc_arena(arena);
				ft_putstr("\n");
				arena = arena->next;
			}
	}
}

void      show_alloc_info(void)
{
  t_ainfo info;

  info = g_alloc.info;
	ft_putstr("show_alloc_info : \n\n");
  ft_show_alloc_detail("Soft limit max allocated bytes : ", info.rlim_cur, TRUE);
  ft_show_alloc_detail("Hard limit max allocated bytes : ", info.rlim_max, TRUE);
  ft_show_alloc_detail("Size of chunk : ", info.size_chunk, TRUE);
  ft_show_alloc_detail("Size of arena : ", info.size_arena, TRUE);
  ft_show_alloc_detail("Pagesize : ", info.pagesize, TRUE);
  ft_show_alloc_detail("Tiny size request : ", info.tiny_size_request, TRUE);
  ft_show_alloc_detail("Small size request : ", info.small_size_request, TRUE);
  ft_show_alloc_detail("Tiny size arena : ", info.tiny_size_arena, TRUE);
  ft_show_alloc_detail("Small size arena : ", info.small_size_arena, TRUE);
}

void				show_alloc_mem(void)
{
	ft_show_alloc(TRUE);
}

void      show_alloc_state(void)
{
		ft_show_alloc(FALSE);
}