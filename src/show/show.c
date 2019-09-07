# include "show.h"

static void		ft_show_arena_head(t_anode *arena_head, t_aarena arena)
{
		const char *arena_name[ALLOC_NONE] = { "TINY : ", "SMALL : ", "LARGE : " };

		ft_putstr(arena_name[arena]);
		if (arena_head != NULL)
				ft_show_address((FT_ALLOC_UINT)arena_head);
		ft_putstr("\n");
}

static void		ft_show_node_size(t_anode *node, size_t node_size)
{
    ft_show_address((FT_ALLOC_UINT)node + FT_ALLOC_SIZE_NODE);
    ft_putstr(" - ");
    ft_show_address((FT_ALLOC_UINT)node + FT_ALLOC_SIZE_NODE + node_size);
    ft_putstr(" : ");
    ft_putnbr(node_size);
    ft_putstr(" bytes\n");
}

static void		ft_show_alloc(t_bool free)
{
		t_aarena 	arena;
		t_anode	*node;

		arena = -1;
		node = NULL;
		while (++arena < ALLOC_NONE)
		{
				node = g_alloc_state.alloc_arena[arena];
				ft_show_arena_head(node, arena);
				while(g_alloc_state.alloc_arena[arena] && node->next != g_alloc_state.alloc_arena[arena])
				{
						if (node->free == free)
							ft_show_node_size((void *)node, node->size);
						node = node->next;
				}
				if (g_alloc_state.alloc_arena[arena] && node->free == free)
					ft_show_node_size((void *)node, node->size);
				ft_putstr("Total : ");
				// if (free == TRUE)
				// 		ft_putnbr(g_alloc_state.total_unused[arena_map]);
				// else
				// 		ft_putnbr(g_alloc_state.total_allocated[arena_map]);
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
