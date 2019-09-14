# include "test.h"
void		*ft_alloc_mmap_test(FT_ALLOC_UINT size)
{
	void	*anon;

	anon = NULL;
	if ((anon = mmap(NULL, size,
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (anon);
}

void test_malloc()
{
	printf("\n===== start test_malloc =====\n");

	printf("\n astate : %ld \n", sizeof(t_astate));

	void *s = ft_malloc(150);
	 void *s2 = ft_malloc(20);
	void *s3 =	 ft_malloc(20);
	void *s4=ft_malloc(1024);
	// printf("\n");
	// printf("\n\n Allocated: \n\n");
	// show_alloc_mem();
	//  printf("Free: \n");
	// show_alloc_mem_free();

	// void *s2 = ft_realloc(s, 40);

	// printf("\n\n Allocated: \n\n");
	// show_alloc_mem();
	//  printf("Free: \n");
	// show_alloc_mem_free();



	//  ft_free(s2);
	// // // ft_free(s2);
	// // // // ft_free(s3);
	// // // ft_free(s4);


	ft_show_alloc_info();
	printf("\n\n Allocated: \n\n");
	 show_alloc_mem();
	 printf("\n\n Free: \n\n");
	show_alloc_mem_free();



	printf("\n===== end test_malloc =====\n");
}
