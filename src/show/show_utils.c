#include "show.h"

size_t		ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void    	ft_strrev(char *s)
{
    size_t 	len;
    size_t 	i;
    char 	c;

    len = ft_strlen(s);
    i = -1;
    c = '\0';
    while (++i < --len)
    {
        c = s[i];
        s[i] = s[len];
        s[len] = c;
    }
}

char    	*ft_itoa(int input, char *buffer, int radix)
{
	size_t	i;
    char    sign;
    int     tmp;

	i = 0;
    sign = '\0';
    tmp = 0;
    if (input == 0)
        buffer[i++] = '0';
    if (input < 0)
    {
        sign = '-';
        input = -input;
    }
	while (input > 0)
    {
        tmp = (input % radix);
    	buffer[i++] = (tmp < 10) ? tmp + 48 : tmp + 87;
        input /= radix;
    }
    if (sign != '\0')
        buffer[i++] = sign;
    buffer[i] = '\0';
    ft_strrev(buffer);
}

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

int		ft_putchar(int c)
{
	return ((int)write(1, &c, 1));
}

void	ft_putstr(const char *s)
{
    while (*s)
    {
        ft_putchar(*s);
        s++;
    }
}

void        ft_show_address(FT_ALLOC_UINT quotient)
{
	char    hexaNumber[9];
	int     tmp;
	int     i;
    
    tmp = 0;
    i = 0;
	while (quotient != 0)
	{
		tmp = quotient % 16;
		if (tmp < 10)
			tmp = tmp + 48;
		else
			tmp = tmp + 87; // 55
		hexaNumber[i++] = tmp;
		quotient = quotient / 16;
	}
	hexaNumber[i] = '0';

	ft_putstr("0x");
	while (--i > -1)
		ft_putchar(hexaNumber[i]);
}

// void    ft_show_blockarena(void *ptr, size_t size_arena)
// {
// 	if (size_arena == FT_ALLOC_TINY)
// 		ft_putstr("TINY : ");
// 	else if (size_arena == FT_ALLOC_SMALL)
// 		ft_putstr("SMALL : ");
// 	else
// 		ft_putstr("LARGE : ");
//     ft_show_address((FT_ALLOC_UINT)ptr);
// 	ft_putstr("\n");
// }

// void    ft_show_blockdata(void *ptr, size_t size)
// {
//     ft_show_address((FT_ALLOC_UINT)ptr + sizeof(t_node));
//     ft_putstr(" - ");
//     ft_show_address((FT_ALLOC_UINT)ptr + sizeof(t_node) + size);
//     ft_putstr(" : ");
//     ft_putnbr(size);
//     ft_putstr(" bytes\n");
// }