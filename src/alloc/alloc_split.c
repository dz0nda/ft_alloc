#include "alloc.h"

static int ft_alloc_split_modifier(size_t nodesize, size_t size)
{
	if (!(nodesize > (size + FT_ALLOC_SIZE_META)))
		return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		ft_alloc_split(t_anode *node, size_t size)
{
	t_anode *new;

	new = NULL;
  if (ft_alloc_split_modifier(node->size, size) == EXIT_FAILURE)
    return (EXIT_FAILURE);
	new = (t_anode *)((FT_ALLOC_UINT)node + FT_ALLOC_SIZE_META + size);
	new->size = node->size - (FT_ALLOC_SIZE_META + size);
	new->free = TRUE;
	node->size = size;
	new->next = node->next;
	new->prev = node;
	node->next->prev = new;
	node->next = new;
	return (EXIT_SUCCESS);
}