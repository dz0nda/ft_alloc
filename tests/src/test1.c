#include <stdlib.h>

int	main(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}