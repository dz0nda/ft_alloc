/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/05 03:43:59 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/05 03:46:20 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_malloc(size_t size)
{
	t_anode	**head;
	t_anode	*node;

	head = NULL;
	if (ft_alloc_init_modifier() == EXIT_SUCCESS)
		if (ft_alloc_init() == EXIT_FAILURE)
			return (NULL);
	size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
	head = ft_alloc_get_arena(size);
	if ((node = ft_alloc_search(head, size)) == NULL)
	{
		if (ft_alloc_arena(head, size) == EXIT_FAILURE)
			return (NULL);
		node = (*head)->prev;
	}
	if (node->size > (size + FT_ALLOC_SIZE_NODE + FT_ALLOC_ALIGNMENT))
		ft_alloc_arena_split(node, size);
	ft_ainfo_rall(ft_alloc_get_target(node->size), node->size, FALSE);
	node->free = FALSE;
	return ((void *)(node + 1));
}