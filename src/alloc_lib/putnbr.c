#include "alloc_lib.h"

void		ft_putnbr(int nb)
{
    char	s[12];

    if (nb == 0)
        ft_putstr("0");
    else if (nb <= -2147483648)
		ft_putstr("-2147483648");
	else if (nb >= 2147483647)
		ft_putstr("2147483647");
    else
    {
        ft_itoa(nb, s, 10);
        ft_putstr(s);
    }
}