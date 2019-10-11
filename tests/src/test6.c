#include <unistd.h>
#include <string.h>
#include "../../ft_liballoc.h"

int		main(void)
{
	void *p = malloc(1024);
	malloc(1024 * 32);
	void *p2 = malloc(1024 * 1024);
	// malloc(1024 * 1024 * 16);
	void *p3 = malloc(1024 * 1024 * 128);
	// free(p);
	// free(p2);
	// free(p3);
	show_alloc_mem();
	ft_putstr("\n");
	show_alloc_mem_details();
	ft_putstr("\n");
	show_alloc_info();
	ft_putstr("\n");
	show_alloc_history();
}