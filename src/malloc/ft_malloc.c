/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_malloc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:42:48 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 06:22:48 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*malloc(size_t size)
{
	t_aarena	**arena;
	t_achunk	*chunk;
	void		*new;

	arena = NULL;
	chunk = NULL;
	new = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return (NULL);
	if (g_alloc.info.pagesize != 0 || ft_alloc_init() == EXIT_SUCCESS)
	{
		size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
		arena = ft_alloc_get_arena_by_size_request(size);
		if (arena == NULL || (chunk = ft_alloc_search_chunk_by_size(*arena, size)) == NULL)
			chunk = ft_alloc_arena_new(arena, size);
		if (chunk != NULL)
		{
			ft_alloc_chunk_split(*arena, chunk, size);
			ft_alloc_state_swap((*arena)->aindex, chunk->size, FALSE);
			chunk->free = FALSE;
			new = (void *)((FT_ALLOC_UINT)chunk + g_alloc.info.size_chunk);
		}
	}
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return (NULL);
	return (new);
}