#include "ft_alloc.h"

void		        *ft_alloc_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n-- > 0)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
}

void				*ft_alloc_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	unsigned char	set;

	s = (unsigned char *)b;
	set = (unsigned char)c;
	while (len-- > 0)
	{
		*s = set;
		s++;
	}
	return (b);
}
