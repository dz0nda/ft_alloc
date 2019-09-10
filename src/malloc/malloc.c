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
	t_anode	*node;

	node = NULL;
	if (g_alloc_state.init == FALSE && ft_alloc_init() == EXIT_FAILURE)
		return (NULL);
	size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
	if ((node = ft_alloc_search_node_by_size(size)) == NULL)
		if ((node = ft_alloc_arena_new_by_size(size)) == NULL)
			return (NULL);
	if (ft_alloc_arena_split(node, size) == EXIT_SUCCESS)
	{
		printf("here");
		ft_alloc_info_free(node->size, FALSE);

	}
	ft_alloc_info_used_free(node->size, FALSE);
	node->free = FALSE;
	return ((void *)(node + 1));
}