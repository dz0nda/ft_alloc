/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_show_mem.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:38:17 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 21:51:39 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_show.h"

static void			ft_show_anames(t_aarena *arena, t_aindex i, t_bool free)
{
	const char	*anames[FT_ALLOC_NONE] = { "TINY : ", "SMALL : ", "LARGE : " };
	FT_AUINT	size;
	FT_AUINT	addr;

	size = g_alloc.info.size_arena;
	addr = (FT_AUINT)arena;
	ft_putstr(anames[i]);
	if (free == FT_TRUE)
	{
		ft_show_alloc_detail("arenas", g_alloc.state.nbrarenas[i], FT_FALSE, COLOR_BOLD);
		ft_show_alloc_detail("chunks", g_alloc.state.nbrchunks[i], FT_FALSE, COLOR_BOLD);
		ft_show_alloc_detail("mmap", g_alloc.state.mmap[i], FT_FALSE, COLOR_BLUE);
		ft_show_alloc_detail("used", g_alloc.state.used[i], FT_FALSE, COLOR_RED);
		ft_show_alloc_detail("freed", g_alloc.state.freed[i], FT_FALSE, COLOR_GREEN);
		ft_show_alloc_detail("overhead", g_alloc.state.ovhead[i], FT_FALSE, COLOR_YELLOW);
	}
	else
		ft_puthexa(addr + size);
	ft_putstr("\n");
}

static void			ft_show_alloc(t_aarena *arena, t_bool free)
{
	t_achunk	*chunk;
	FT_AUINT	size;
	FT_AUINT	addr;

	chunk = NULL;
	while (arena)
	{
		size = g_alloc.info.size_arena;
		addr = (FT_AUINT)arena;
		if (free == FT_TRUE)
			ft_show_alloc_addr((addr + size), arena->size - size, -1);
		if ((chunk = arena->head) != NULL)
			while (chunk != NULL)
			{
				if (free == chunk->free || free == FT_TRUE)
				{
					size = g_alloc.info.size_chunk;
					addr = (FT_AUINT)chunk;
					ft_putstr(" - ");
					ft_putnbr(chunk->free);
					ft_show_alloc_addr((addr + size), chunk->size, chunk->free);
				}
				chunk = chunk->next;
			}
		arena = arena->next;
	}
}

void				show_alloc_mem(void)
{
	size_t		total;
	t_aindex	i;
	t_aarena	*arena;

	total = 0;
	i = -1;
	arena = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return ;
	ft_putstr("|| show_alloc_mem ||\n\n");
	while (++i < FT_ALLOC_NONE)
		if ((arena = g_alloc.arena[i]) != NULL)
		{
			ft_show_anames(arena, i, FT_FALSE);
			total += g_alloc.state.used[i];
			ft_show_alloc(arena, FT_FALSE);
		}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" bytes\n");
	ft_putstr("\n");
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return ;
}

void				show_alloc_mem_details(void)
{
	t_aindex	i;
	t_aarena	*arena;

	i = -1;
	arena = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return ;
	ft_putstr("|| show_alloc_mem_details ||\n\n");
	while (++i < FT_ALLOC_NONE)
		if ((arena = g_alloc.arena[i]) != NULL)
		{
			ft_show_anames(arena, i, FT_TRUE);
			ft_show_alloc(arena, FT_TRUE);
		}
	ft_putstr("\n");
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return ;
}
