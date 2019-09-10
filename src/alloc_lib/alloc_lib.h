#ifndef FT_ALLOC_LIB_H
# define FT_ALLOC_LIB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char    *ft_itoa(int input, char *buffer, int radix);
void	  *ft_memset(void *b, int c, size_t len);
void    ft_show_address(size_t quotient, int endl);
int		  ft_putchar(int c);
void		ft_putnbr(int nb);
void	  ft_putstr(const char *s);
size_t	ft_strlen(const char *s);
void    ft_strrev(char *s);

#endif