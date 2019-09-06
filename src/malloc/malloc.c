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
	t_node	**head;
	t_node	*node;

	head = NULL;
	size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
	head = ft_alloc_get_arena(size);
	if ((node = ft_alloc_search(head, size)) == NULL)
	{
		if (ft_alloc_arena(head, ft_alloc_get_size_arena(size)) == EXIT_FAILURE)
			return (NULL);
		node = (*head)->prev;
	}
	if (node->size > (size + FT_ALLOC_SIZE_NODE + FT_ALLOC_ALIGNMENT))
		ft_alloc_arena_split(node, size);
	node->free = FALSE;
	// ft_display(*head);
	return (NULL);
}