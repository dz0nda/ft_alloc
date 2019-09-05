#ifndef FT_SHOW_H
# define FT_SHOW_H

# include "../alloc/alloc.h"

void    show_alloc_mem(void);
void    show_alloc_mem_free(void);
void    ft_show_address(FT_ALLOC_UINT quotient);
void	  ft_putstr(const char *s);
int		  ft_putchar(int c);
void		ft_putnbr(int nb);

#endif
