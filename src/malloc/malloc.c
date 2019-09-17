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
#include "../show/show.h"

void	*ft_malloc(size_t size)
{
	t_aarena	**arena;
	t_achunk	*chunk;
	void			*new;

	arena = NULL;
	chunk = NULL;
	new = NULL;
	pthread_mutex_lock(&g_mutex);
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
				new = (void *)(chunk + 1);
		}
	}
	pthread_mutex_unlock(&g_mutex);
	return (new);
}