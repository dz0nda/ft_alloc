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
	t_aarena	**arena;
	t_achunk	*node;

	arena = NULL;
	node = NULL;
	size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
	arena = ft_alloc_get_arena_by_size(size);
	if (g_alloc_state.init == FALSE)
		ft_alloc_init();
	if (arena && (node = ft_alloc_search_chunk_by_size(*arena, size)) == NULL)
		if ((node = ft_alloc_arena_mmap(arena, size)) == NULL)
			return (NULL);
	ft_alloc_chunk_split(*arena, node, size);
	ft_alloc_info_total(*arena, node->size, FALSE);
	node->free = FALSE;
	return ((void *)(node + 1));
}