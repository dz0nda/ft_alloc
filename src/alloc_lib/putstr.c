#include "alloc_lib.h"

void	ft_putstr(const char *s)
{
    while (*s)
    {
        ft_putchar(*s);
        s++;
    }
}