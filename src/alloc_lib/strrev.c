#include "alloc_lib.h"

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