/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_show_hexa.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:39:56 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 01:21:20 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_libft.h"

static size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

static char		*ft_strrev(char *s)
{
	size_t		len;
	size_t		i;
	char		c;

	if ((len = ft_strlen(s)) == 0)
		return (NULL);
	len -= 1;
	i = 0;
	c = '\0';
	while (i < len)
	{
		c = s[i];
		s[i++] = s[len];
		s[len--] = c;
	}
	return (s);
}

static char		*ft_itoa(int input, char *buffer, int radix)
{
	size_t		i;
	char		sign;
	int			tmp;

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
	return (ft_strrev(buffer));
}

void			ft_puthexa(size_t nb)
{
	char	s[17];
	int		i;
	int		tmp;

	ft_memset(s, '\0', sizeof(s));
	i = 0;
	tmp = 0;
	ft_putstr("0x");
	while (nb != 0)
	{
		tmp = nb % 16;
		s[i++] = (tmp < 10) ? tmp + 48 : tmp + 87;
		nb /= 16;
	}
	ft_strrev(s);
	ft_putstr(s);
}

void			ft_putnbr(int nb)
{
	char		s[12];

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
