# include "test.h"

void test_malloc()
{
	printf("\n===== start test_malloc =====\n");


	printf("%ld %ld", sizeof(unsigned long), sizeof(size_t));

	ft_malloc(20);
	ft_malloc(400);
	ft_malloc(350);
	ft_malloc(45);
	ft_malloc(3500);

	show_alloc_mem();
	printf("\n");
	show_alloc_mem_free();

	printf("\n===== end test_malloc =====\n");
}
