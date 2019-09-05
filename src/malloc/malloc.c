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
		if ((node = ft_alloc_search(head, size)) == NULL)
			return (NULL);
	}
	if (node->size > (size + FT_ALLOC_SIZE_NODE))
		ft_alloc_split_node(node, size);
	node->size = size;
	node->free = FALSE;
	return (NULL);
}
