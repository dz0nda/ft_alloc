# include "show.h"

static void		ft_show_node(t_achunk *node, t_bool free)
{
	FT_ALLOC_UINT address;
	FT_ALLOC_UINT size;

	address = (FT_ALLOC_UINT)node;
	size = (FT_ALLOC_UINT)node->size;
	if (node->free == free)
	{
		ft_show_address(address + FT_ALLOC_SIZE_CHUNK, 0);
		ft_putstr(" - ");
		ft_show_address(address + FT_ALLOC_SIZE_CHUNK + size, 0);
		ft_putstr(" : ");
		ft_putnbr(size);
		ft_putstr(" bytes \n");
	}
}

static void 	ft_show_iter(t_achunk *head, t_bool free, void (*f)(t_achunk *node, t_bool free))
{
	t_achunk *node;

	if ((node = head) == NULL)
		return ;
	f(node, free);
	while ((node = node->next) != head)
		f(node, free);
}

 static void		ft_show_alloc(t_bool free)
 {
		const char *aindex[ALLOC_NONE] = { "TINY : ", "SMALL : ", "LARGE : " };
		t_aindex 	index;
		t_aarena	*arena;

		index = -1;
		arena = NULL;
		while (++index < ALLOC_NONE)
		{
			arena = g_alloc_state.alloc_arena[index];
			if (arena)
			{
				while (arena)
				{
					ft_putstr(aindex[index]);
					(arena) ? ft_show_address((FT_ALLOC_UINT)arena->head, 1) : ft_show_address(0, 1);
					ft_show_iter(arena->head, free, ft_show_node);
					arena = arena->next;
				}
				if (free == TRUE)
					ft_putnbr(g_alloc_state.alloc_info.a_freed[index]);
				else
					ft_putnbr(g_alloc_state.alloc_info.a_used[index]);
				ft_putstr(" bytes \n");
			}
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
