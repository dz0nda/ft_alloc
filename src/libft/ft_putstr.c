#include "ft_libft.h"

void	ft_putstr(const char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}

void	ft_putstr_color(const char *s, int color)
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