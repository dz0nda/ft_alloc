/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_show_tools.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:40:08 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 06:24:44 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_show.h"

void	ft_putstr(const char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}

void	ft_putstr_color(const char *s, t_acolor color)
{
	if (color == COLOR_RED)
		ft_putstr(FT_CRED);
	else if (color == COLOR_GREEN)
		ft_putstr(FT_CGREEN);
	else if (color == COLOR_YELLOW)
		ft_putstr(FT_CYELLOW);
	else if (color == COLOR_BLUE)
		ft_putstr(FT_CBLUE);
	else if (color == COLOR_BOLD)
		ft_putstr(FT_CBOLD);
	ft_putstr(s);
	ft_putstr(FT_CSTOP);
}

void	ft_show_alloc_addr(FT_AUINT ptr, FT_AUINT size, t_bool free)
{
	ft_puthexa(ptr);
	ft_putstr(" - ");
	ft_puthexa(ptr + size);
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" bytes");
	if (free == FT_FALSE || free == FT_TRUE)
	{
		ft_putstr(" -> ");
		(free == FT_FALSE) ? ft_putstr_color("used", COLOR_RED) :
			ft_putstr_color("freed", COLOR_GREEN);
	}
	ft_putstr("\n");
}

void	ft_show_alloc_detail(const char *s, FT_AUINT nb, t_bool dl,
		t_acolor color)
{
	ft_putstr(" - ");
	ft_putstr_color(s, color);
	ft_putstr(" : ");
	ft_putnbr(nb);
	if (color != COLOR_BOLD)
		ft_putstr(" bytes ");
	else
		ft_putstr(" ");
	if (dl == FT_TRUE)
		ft_putstr("\n");
}
