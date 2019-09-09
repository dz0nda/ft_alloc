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
	node = NULL;
	if (g_alloc_state.init == FALSE && ft_alloc_init() == EXIT_FAILURE)
		return (NULL);
	size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
	head = ft_alloc_get_arena_by_size(size);
	if ((node = ft_alloc_search_node_by_size(size)) == NULL)
		if ((node = ft_alloc_arena_new(size)) == NULL)
			return (NULL);
	if (node->size > (size + FT_ALLOC_SIZE_NODE + FT_ALLOC_ALIGNMENT))
		ft_alloc_arena_split(node, size);
	// ft_ainfo_rall(ft_alloc_get_target(node->size), node->size, FALSE);
	node->free = FALSE;
	return ((void *)(node + 1));
}