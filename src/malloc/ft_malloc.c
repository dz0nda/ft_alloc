/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:42:48 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 02:48:02 by dz0nda           ###   ########.fr       */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		*ft_malloc(size_t size)
{
	t_aarena	**arena;
	t_achunk	*chunk;

	arena = NULL;
	chunk = NULL;
	size = ft_alloc_get_size_aligned(size, FT_AALIGNMENT);
	arena = ft_alloc_get_arena_by_size_request(size);
	if (arena == NULL || (chunk = ft_alloc_search_chunk_by_size(*arena, size)) == NULL)
		if ((chunk = ft_alloc_arena_new(arena, size)) == NULL)
			return (NULL);
	ft_alloc_chunk_split(*arena, chunk, size);
	ft_alloc_state_swap((*arena)->aindex, chunk->size, FT_FALSE);
	chunk->free = FT_FALSE;
	ft_alloc_history(chunk, (*arena)->aindex, FT_MALLOC);
	return ((void *)((FT_AUINT)chunk + g_alloc.info.size_chunk));
}

void			*malloc(size_t size)
{
	void	*new;

	new = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return (NULL);
	if (g_alloc.info.pagesize != 0 || ft_alloc_init() == EXIT_SUCCESS)
		new = ft_malloc(size);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return (NULL);
	return (new);
}
