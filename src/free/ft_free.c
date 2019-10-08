/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:36:54 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 06:07:07 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_free.h"

static void			ft_free(void *ptr)
{
	t_aarena	**arena;
	t_achunk	*chunk;

	arena = NULL;
	chunk = NULL;
	if ((ptr != NULL) && ((arena = ft_alloc_search_arena_by_address(ptr)) != NULL))
	{
		if ((chunk = ft_alloc_search_chunk_by_address(*arena, ptr)) != NULL)
		{
			chunk->free = FT_TRUE;
			ft_alloc_state_swap((*arena)->aindex, chunk->size, FT_TRUE);
			ft_alloc_chunk_concat(*arena, chunk);
			if (((*arena)->head->size + g_alloc.info.size_arena + g_alloc.info.size_chunk) == (*arena)->size)
				if ((*arena)->prev != NULL || (*arena)->aindex == ALLOC_LARGE)
					ft_alloc_arena_del(arena);
		}
	}
}

void			free(void *ptr)
{
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return ;
	ft_free(ptr);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return ;
}
