# include "test.h"

void test_malloc()
{
	printf("\n===== start test_malloc =====\n");

	void *s = ft_malloc(20);
	//  ft_malloc(20);

	//  ft_malloc(20);
//void *s2 = ft_malloc(20);
	//  ft_malloc(350);
	// ft_malloc(45);
// void *s3 =	 ft_malloc(3500);

	// ft_show_alloc_info();
	// printf("\n");
	// show_alloc_mem();
	// printf("\n");
	// show_alloc_mem_free();
	// printf("\n\n\n");



	// ft_show_alloc_info();
	// printf("\n");
	show_alloc_mem();
	printf("\n");
	show_alloc_mem_free();

	printf("\n===== end test_malloc =====\n");
}
