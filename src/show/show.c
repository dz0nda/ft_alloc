# include "show.h"

static void		ft_show_alloc(t_bool free)
{
	const char *aindex[ALLOC_NONE] = { "TINY : ", "SMALL : ", "LARGE : " };
  t_aindex i;
  t_astate state;
	t_aarena arena;

	i = -1;
  state = g_alloc.state;
	ft_putstr("show_alloc_mem :\n");
	while (++i < ALLOC_NONE)
	{
		if (state.arena[i] != NULL)
		{
			ft_putstr(aindex[i]);
			ft_show_alloc_addr((FT_ALLOC_UINT)state.arena[i]->head, state.arena[i]->size - g_alloc.info.size_arena);
			ft_show_alloc_arena(state.arena[i], free);
		}
	}
}

void				show_alloc_mem(void)
{
		ft_show_alloc(FALSE);
}

void    		show_alloc_mem_free(void)
{
		ft_show_alloc(TRUE);
}
