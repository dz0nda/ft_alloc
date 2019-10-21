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

static size_t 	ft_show_addr(FT_AUINT ptr, FT_AUINT size, t_bool details, int i)
{
	const char		*state[4] = { "mmap", "used", "freed", "overhead" };
	const t_acolor	color[4] = { COLOR_BLUE, COLOR_RED, COLOR_GREEN, COLOR_YELLOW };

	if (ptr != 0)
	{
		ft_puthexa(ptr);
		ft_putstr(" - ");
		ft_puthexa(ptr + size);
		ft_putstr(" : ");
	}
	ft_putnbr(size);
	ft_putstr(" bytes");
	if (details == FT_TRUE)
	{
		ft_putstr(" -> ");
		ft_putstr_color(state[i], color[i]);
	}
	ft_putstr("\n");
	return (size);
}

static void 		ft_show_alloc_chunks(size_t total[4], t_achunk *chunk, t_bool details)
{
	size_t 	size;

	size = g_alloc.info.size_chunk;
	if (details == FT_TRUE || (details == FT_FALSE && chunk->free == FT_FALSE))
		ft_putstr(" - ");
	if (details == FT_TRUE)
	{
		total[3] += ft_show_addr((FT_AUINT)chunk, size, FT_TRUE, 3);
		ft_putstr(" - ");
		if (chunk->free == FT_TRUE)
			total[2] += ft_show_addr((FT_AUINT)chunk + size, chunk->size, FT_TRUE, 2);
		else
			total[1] += ft_show_addr((FT_AUINT)chunk + size, chunk->size, FT_TRUE, 1);
	}
	if (details == FT_FALSE && chunk->free == FT_FALSE)
		total[1] += ft_show_addr((FT_AUINT)chunk + size, chunk->size, FT_FALSE, -1);
}

static void			ft_show_alloc(size_t total[4], t_aarena *arena, t_bool details)
{
	const char	*anames[FT_ALLOC_AINDEX_MAX] = { "TINY : ", "SMALL : ", "LARGE : " };
	size_t size;
	t_achunk	*chunk;

	size = g_alloc.info.size_arena;
	while (arena && arena->head != NULL)
	{
		ft_putstr(anames[arena->aindex]);
		if (details == FT_TRUE)
		{
			total[0] += ft_show_addr((FT_AUINT)arena, arena->size, FT_TRUE, 0);
			total[3] += ft_show_addr((FT_AUINT)arena, size, FT_TRUE, 3);
		}
		else
		{
			ft_puthexa((FT_AUINT)arena);
			ft_putstr("\n");
		}
		chunk = arena->head;
		while (chunk != NULL)
		{
			ft_show_alloc_chunks(total, chunk, details);
			chunk = chunk->next;
		}
		arena = arena->next;
	}
}

void				show_alloc_mem(void)
{
	size_t		total[4];
	t_aindex	i;
	t_aarena	*arena;

	i = -1;
	arena = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return ;
	ft_putstr("|| show_alloc_mem ||\n\n");
	while (++i < FT_ALLOC_AINDEX_MAX)
		if ((arena = g_alloc.arena[i]) != NULL)
			ft_show_alloc(total, arena, FT_FALSE);
	ft_putstr("Total : ");
	ft_show_addr(0, total[1], FT_FALSE, -1);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return ;
}

void				show_alloc_mem_state(void)
{
	size_t		total[4];
	int	i;
	t_aarena	*arena;

	i = -1;
	arena = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return ;
	ft_putstr("|| show_alloc_mem ||\n\n");
	while (++i < FT_ALLOC_AINDEX_MAX)
		if ((arena = g_alloc.arena[i]) != NULL)
			ft_show_alloc(total, arena, FT_TRUE);
	i = -1;
	ft_putstr("Total :\n");
	while (++i < 4)
		ft_show_addr(0, total[i], FT_TRUE, i);
	ft_putstr("\n");
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return ;
}
