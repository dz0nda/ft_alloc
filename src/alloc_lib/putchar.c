#include "alloc_lib.h"

int		ft_putchar(int c)
{
	return ((int)write(1, &c, 1));
}