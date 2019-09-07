#include "alloc_lib.h"

void        ft_show_address(size_t quotient)
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