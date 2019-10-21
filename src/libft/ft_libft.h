
#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <unistd.h>

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

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_putstr(const char *s);
void	        ft_putstr_color(const char *s, int color);
void			ft_puthexa(size_t nb);
void			ft_putnbr(int nb);

#endif