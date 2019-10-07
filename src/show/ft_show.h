/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_show.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:40:49 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/23 21:02:53 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SHOW_H
# define FT_SHOW_H

# include "../alloc/ft_alloc.h"

# define FT_CRED		"\033[0;31m"
# define FT_CGREEN		"\033[0;32m"
# define FT_CYELLOW		"\033[0;33m"
# define FT_CBLUE		"\033[0;34m"
# define FT_CBOLD		"\033[1m"
# define FT_CSTOP		"\033[0;m"

typedef enum	e_alloc_color
{
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_BLUE,
	COLOR_BOLD
}				t_acolor;

void			ft_puthexa(FT_AUINT nb);
void			ft_putnbr(int nb);

void			show_alloc_mem(void);
void			show_alloc_mem_details(void);
void			show_alloc_info(void);
void			ft_show_alloc_history(void);
void 			ft_show_alloc(t_aarena *arena, t_bool free);

void			ft_putstr(const char *s);
void			ft_putstr_color(const char *s, t_acolor color);
void			ft_show_alloc_addr(FT_AUINT ptr, FT_AUINT size, t_bool free);
void			ft_show_alloc_detail(const char *s, FT_AUINT nb, t_bool dl, t_acolor color);

#endif
