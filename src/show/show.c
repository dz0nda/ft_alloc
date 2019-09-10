# include "show.h"

static void		ft_show_node(t_anode *node, t_bool free)
{
	FT_ALLOC_UINT address;
	FT_ALLOC_UINT size;

	address = (FT_ALLOC_UINT)node;
	size = (FT_ALLOC_UINT)node->size;
	if (node->free == free)
	{
		ft_show_address(address + FT_ALLOC_SIZE_NODE, 0);
		ft_putstr(" - ");
		ft_show_address(address + FT_ALLOC_SIZE_NODE + size, 0);
		ft_putstr(" : ");
		ft_putnbr(size);
		ft_putstr(" bytes \n");
	}
}

static void 	ft_show_iter(t_anode *head, t_bool free, void (*f)(t_anode *node, t_bool free))
{
	t_anode *node;

	if ((node = head) == NULL)
		return ;
	f(node, free);
	while ((node = node->next) != head)
		f(node, free);
}

static void		ft_show_alloc(t_bool free)
{
	const char *arena[ALLOC_NONE] = { "TINY : ", "SMALL : ", "LARGE : " };
	t_aarena 	index;
	t_anode	*node;

	index = -1;
	node = NULL;
	while (++index < ALLOC_NONE)
	{
		ft_putstr(arena[index]);
		if ((node = g_alloc_state.alloc_arena[index]) != NULL)
			ft_show_address((FT_ALLOC_UINT)node, 1);
		ft_show_iter(node, free, ft_show_node);
		ft_putstr("Total : ");
		if (free == TRUE)
				ft_putnbr(g_alloc_state.alloc_info.a_free[index]);
		else
				ft_putnbr(g_alloc_state.alloc_info.a_used[index]);
		ft_putstr(" bytes \n");
	}
}

void				show_alloc_mem(void)
{
		ft_show_alloc(FALSE);
}

void    		show_alloc_mem_free(void)
{
		ft_show_alloc(TRUE);
}
