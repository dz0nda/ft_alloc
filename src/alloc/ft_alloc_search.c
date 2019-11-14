/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_search.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:07:58 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 06:52:18 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

t_aarena		**ft_alloc_search_arena_by_address(void *ptr)
{
	t_aindex index;
	t_aarena **arena;
	FT_AUINT addr_ptr;
	FT_AUINT addr_arena;

	index = -1;
	arena = NULL;
	addr_ptr = (FT_AUINT)ptr;
	while (++index < FT_ALLOC_AINDEX_MAX)
	{
		arena = &g_alloc.arena[index];
		while (arena && *arena != NULL)
		{
			addr_arena = (FT_AUINT)(*arena);
			if ((addr_arena) <= addr_ptr &&
				addr_ptr <= (addr_arena + (*arena)->size))
				return (arena);
			arena = &(*arena)->next;
		}
	}
	return (NULL);
}

t_achunk		**ft_alloc_search_achunk_by_address(void *ptr)
{
	t_aarena **arena;
	t_achunk **chunk;
	FT_AUINT addr_ptr;
	FT_AUINT addr_chunk;

	if ((arena = ft_alloc_search_arena_by_address(ptr)) == NULL)
		return (NULL);
	addr_ptr = (FT_AUINT)ptr;
	if (arena && *arena && (chunk = &(*arena)->head) != NULL)
		while (*chunk != NULL)
		{
			addr_chunk = (FT_AUINT)((FT_AUINT)(*chunk) + g_alloc.info.s_chunk);
			if (addr_chunk == addr_ptr)
				return (chunk);
			chunk = &(*chunk)->next;
		}
	return (NULL);
}

t_achunk		*ft_alloc_search_chunk_by_address(void *ptr)
{
	t_aarena **arena;
	t_achunk *chunk;
	FT_AUINT addr_ptr;
	FT_AUINT addr_chunk;

	if ((arena = ft_alloc_search_arena_by_address(ptr)) == NULL)
		return (NULL);
	addr_ptr = (FT_AUINT)ptr;
	if (arena && *arena && (chunk = (*arena)->head) != NULL)
		while (chunk != NULL)
		{
			addr_chunk = (FT_AUINT)((FT_AUINT)chunk + g_alloc.info.s_chunk);
			if (addr_chunk == addr_ptr)
				return (chunk);
			chunk = chunk->next;
		}
	return (NULL);
}

t_achunk		*ft_alloc_search_chunk_by_size(size_t size)
{
	t_aarena	**arena;
	t_achunk	*chunk;

	if (size > g_alloc.info.s_small_request)
		return (NULL);
	arena = ft_alloc_get_arena_by_size(size);
	while (arena && *arena && (chunk = (*arena)->head) != NULL)
	{
		while (chunk != NULL)
		{
			if (chunk->size >= size && chunk->free == FT_TRUE)
				return (chunk);
			chunk = chunk->next;
		}
		arena = &(*arena)->next;
	}
	return (NULL);
}
