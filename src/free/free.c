/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:36:54 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 07:57:30 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "free.h"

void			ft_free(void *ptr)
{
	t_aarena	**arena;
	t_achunk	*chunk;

	arena = NULL;
	chunk = NULL;
	pthread_mutex_lock(&g_mutex);
	if ((ptr != NULL) || ((arena = ft_alloc_search_arena_by_address(ptr)) != NULL))
	{
		if ((chunk = ft_alloc_search_chunk_by_address(*arena, ptr)) != NULL)
		{
			chunk->free = TRUE;
			ft_alloc_state_swap((*arena)->aindex, chunk->size, TRUE);
			ft_alloc_chunk_concat(*arena, chunk);
			if (((*arena)->head->size + g_alloc.info.size_arena + g_alloc.info.size_chunk) == (*arena)->size)
				ft_alloc_arena_del(arena);
		}
	}
	pthread_mutex_unlock(&g_mutex);
}
