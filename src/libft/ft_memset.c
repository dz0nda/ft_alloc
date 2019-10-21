#include "ft_libft.h"

void				*ft_memset(void *b, int c, size_t len)
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
