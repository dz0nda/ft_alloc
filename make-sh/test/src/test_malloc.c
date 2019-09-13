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

	printf("\n %ld \n", sizeof(t_alloc_state));

	void *s = ft_malloc(150);
	// void *s2 = ft_malloc(20);
	// void *s3 =	 ft_malloc(20);
	// void *s4=ft_malloc(20);
	printf("\n");
	show_alloc_mem();
	printf("\n");
	show_alloc_mem_free();

	void *s2 = ft_realloc(s, 40);

	// ft_free(s);
	// ft_free(s2);
	// // ft_free(s3);
	// ft_free(s4);


	// ft_show_alloc_info();
	printf("\n");
	show_alloc_mem();
	printf("\n");
	show_alloc_mem_free();



	printf("\n===== end test_malloc =====\n");
}
