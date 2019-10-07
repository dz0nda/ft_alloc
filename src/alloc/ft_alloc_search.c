/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_search.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:07:58 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/23 21:11:06 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

static int		ft_alloc_is_in_arena(t_aarena *arena, void *ptr)
{
	FT_AUINT addr_arena;
	FT_AUINT addr_ptr;

	addr_arena = (FT_AUINT)arena;
	addr_ptr = (FT_AUINT)ptr;
	if ((addr_arena) <= addr_ptr && addr_ptr <= (addr_arena + arena->size))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int		ft_alloc_is_in_chunk(t_achunk *chunk, void *ptr)
{
	FT_AUINT addr_chunk;
	FT_AUINT addr_ptr;

	addr_chunk = (FT_AUINT)((FT_AUINT)chunk + g_alloc.info.size_chunk);
	addr_ptr = (FT_AUINT)ptr;
	// if (addr_chunk <= addr_ptr && addr_ptr <= (addr_chunk + chunk->size))
	// 	return (EXIT_SUCCESS);
	if (addr_chunk == addr_ptr)
		return (EXIT_SUCCESS);	
	return (EXIT_FAILURE);
}

t_aarena		**ft_alloc_search_arena_by_address(void *ptr)
{
	t_aindex index;
	t_aarena **arena;

	index = -1;
	arena = NULL;
	while (++index < ALLOC_NONE)
	{
		arena = &g_alloc.arena[index];
		while (*arena != NULL)
		{
			if (ft_alloc_is_in_arena(*arena, ptr) == EXIT_SUCCESS)
				return (arena);
			arena = &(*arena)->next;
		}
	}
	return (NULL);
}

t_achunk		*ft_alloc_search_chunk_by_address(t_aarena *arena, void *ptr)
{
	t_achunk *chunk;

	if (arena == NULL)
		return (NULL);
	chunk = arena->head;
	if (ft_alloc_is_in_chunk(chunk, ptr) == EXIT_SUCCESS)
		return (chunk);
	while ((chunk = chunk->next) != arena->head)
		if (ft_alloc_is_in_chunk(chunk, ptr) == EXIT_SUCCESS)
			return (chunk);
	return (NULL);
}

t_achunk		*ft_alloc_search_chunk_by_size(t_aarena *arena, size_t size)
{
	t_achunk *chunk;

	chunk = NULL;
	if (size > g_alloc.info.small_size_request)
		return (NULL);
	while (arena && chunk == NULL)
	{
		if ((chunk = arena->head) != NULL)
		{
			while (chunk != NULL)
			{
					if (chunk->size >= size && chunk->free == FT_TRUE)
						return (chunk);
				chunk = chunk->next;
			}
		}
		chunk = NULL;
		arena = arena->next;
	}
	return (NULL);
}
