# include "test.h"

void test_malloc()
{
	printf("\n===== start test_malloc =====\n");

	ft_malloc(3500);

	show_alloc_mem_free();

	printf("\n===== end test_malloc =====\n");
}
