# include "test.h"
# include "string.h"

# define M (1024 * 1024)

void test_malloc_5()
{
	ft_malloc(1024);
	ft_malloc(1024 * 32);
	ft_malloc(1024 * 1024);
	ft_malloc(1024 * 1024 * 16);
	ft_malloc(1024 * 1024 * 128);
	show_alloc_mem();
}

void test_malloc_4()
{
	char	*addr;

	addr = malloc(16);
	ft_free(NULL);
	ft_free((void *)addr + 5);
	if (ft_realloc((void *)addr + 5, 10) == NULL)
		ft_putstr("Bonjours\n");
}

void test_malloc_3()
{
	char	*addr1;
	char	*addr2;
	char	*addr3;

	addr1 = (char *)ft_malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	ft_putstr(addr1);
	addr2 = (char *)ft_malloc(16 * M);
	addr3 = (char *)ft_realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	ft_putstr(addr3);
}

void test_malloc_2()
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)ft_malloc(1024);
		addr[0] = 42;
		ft_free(addr);
		i++;
	}
}

void test_malloc_1()
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)ft_malloc(1024);
		addr[0] = 42;
		i++;
	}
}

void test_malloc_0()
{
		char	*addr;
		int		i;

		i = 0;
		while (i < 1024)
			i++;
	}

void test_malloc()
{
	printf("\n===== start test_malloc =====\n");

	void *s = ft_malloc(20);

	ft_putstr("\n");
	show_alloc_mem();
	ft_putstr("\n");
	show_alloc_mem_free();

		ft_show_alloc_info();
	ft_show_alloc_state();

	ft_free(s);

	ft_putstr("\n");
	show_alloc_mem();
	ft_putstr("\n");
	show_alloc_mem_free();
		ft_show_alloc_info();
	ft_show_alloc_state();

	// ft_show_alloc_info();
	// ft_show_alloc_state();

	// test_malloc_0();
	// test_malloc_1();
	// test_malloc_2();
	// test_malloc_3();
	// test_malloc_4();
	// test_malloc_5();

	printf("\n===== end test_malloc =====\n");
}
