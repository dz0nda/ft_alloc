/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   show.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:38:17 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/23 19:32:23 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "show.h"

static void		ft_show_alloc_state_detail(t_astate state, t_aindex i, int det)
{
	const char	*aindex[ALLOC_NONE] = { "[ TINY ]", "[ SMALL ]", "[ LARGE ]" };

	if (det == 0)
	{
		ft_putstr(aindex[i]);
		ft_show_alloc_detail("arenas", state.nbrarenas[i], FALSE, COLOR_BOLD);
		ft_show_alloc_detail("chunks", state.nbrchunks[i], TRUE, COLOR_BOLD);
	}
	else
	{
		ft_show_alloc_detail("used", state.used[i], FALSE, COLOR_RED);
		ft_show_alloc_detail("freed", state.freed[i], FALSE, COLOR_GREEN);
		ft_show_alloc_detail("overhead", state.ovhead[i], TRUE, COLOR_YELLOW);
	}
}

static void		ft_show_alloc(t_bool details)
{
	t_aindex	i;
	t_astate	state;
	t_aarena	*arena;

	i = -1;
	state = g_alloc.state;
	ft_putstr("show_alloc_mem : \n\n");
	while (++i < ALLOC_NONE)
	{
		if ((arena = state.arena[i]) != NULL)
		{
			ft_show_alloc_state_detail(state, i, 0);
			while (arena)
			{
				ft_show_alloc_state_detail(state, i, 1);
				ft_putstr(" - ");
				ft_show_alloc_addr((FT_ALLOC_UINT)arena->head, arena->size - (g_alloc.info.size_arena + g_alloc.info.size_chunk), -1);
				if (details)
					ft_show_alloc_arena(arena);
				ft_putstr("\n");
				arena = arena->next;
			}
		}
	}
}

void			show_alloc_info(void)
{
	t_ainfo		info;

	info = g_alloc.info;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return ;
	ft_putstr("show_alloc_info : \n\n");
	ft_show_alloc_detail("Soft limit max allocated bytes", info.rlim_cur, TRUE, -1);
	ft_show_alloc_detail("Hard limit max allocated bytes", info.rlim_max, TRUE, -1);
	ft_show_alloc_detail("Size of chunk", info.size_chunk, TRUE, -1);
	ft_show_alloc_detail("Size of arena", info.size_arena, TRUE, -1);
	ft_show_alloc_detail("Pagesize", info.pagesize, TRUE, -1);
	ft_show_alloc_detail("Tiny size request", info.tiny_size_request, TRUE, -1);
	ft_show_alloc_detail("Small size request", info.small_size_request, TRUE, -1);
	ft_show_alloc_detail("Tiny size arena", info.tiny_size_map, TRUE, -1);
	ft_show_alloc_detail("Small size arena", info.small_size_map, TRUE, -1);
	ft_putstr("\n");
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return ;
}

void			show_alloc_mem(void)
{
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return ;
	ft_show_alloc(TRUE);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return ;
}

void			show_alloc_state(void)
{
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return ;
	ft_show_alloc(FALSE);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return ;
}
