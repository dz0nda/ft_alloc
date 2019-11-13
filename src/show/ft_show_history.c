/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_show_history.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 21:22:20 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 23:04:15 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_show.h"

static size_t 	ft_show_addr(FT_AUINT ptr, FT_AUINT size)
{
	if (ptr != 0)
	{
		ft_puthexa(ptr);
		ft_putstr(" - ");
		ft_puthexa(ptr + size);
		ft_putstr(" : ");
	}
	ft_putnbr(size);
	ft_putstr(" bytes");
	return (size);
}

void			show_alloc_history(void)
{
	const char	*anames[FT_ALLOC_AINDEX_MAX] = { "TINY", "SMALL", "LARGE" };
	const char	*ftnames[FT_NONE] = { "MALLOC", "FREE", "REALLOC" };
	t_aindex	aindex;
	t_ahist		*history;
	int			ij[2];

	aindex = -1;
	history = g_alloc.history;
	ij[0] = FT_AHIST;
	ij[1] = 0;
	ft_putstr("|| show_alloc_history ||\n\n");
	while (--ij[0] > -1)
		if (history[ij[0]].addr > 0)
		{
			ft_putnbr(++ij[1]);
			ft_putstr(". ");
			ft_putstr(anames[history[ij[0]].index]);
			ft_putstr("\t");
			ft_putstr(ftnames[history[ij[0]].aft]);
			ft_putstr("\t\t");
			ft_show_addr(history[ij[0]].addr, history[ij[0]].size);
			ft_putstr("\n");
		}
}
