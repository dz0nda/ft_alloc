#include "alloc_lib.h"

void        ft_show_address(size_t quotient, int endl)
{
	char    hexaNumber[17];
	int     tmp;
	int     i;
    
    tmp = 0;
    i = 0;
	ft_memset(hexaNumber, '\0', sizeof(hexaNumber));
	while (quotient != 0)
	{
		tmp = quotient % 16;
		if (tmp < 10)
			tmp = tmp + 48;
		else
			tmp = tmp + 87; // 55
		hexaNumber[i] = tmp;
		quotient = quotient / 16;
		i++;
	}

	ft_putstr("0x");
	while (--i > -1)
		ft_putchar(hexaNumber[i]);
	if (endl)
		ft_putchar('\n');
}