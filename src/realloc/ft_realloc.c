/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:37:50 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 06:23:10 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_realloc.h"

static int		ft_realloc_by_concat(t_aarena *arena, void *ptr, size_t size)
{
	t_achunk	*chunk;
	t_aindex	aindex;

	chunk = NULL;
	aindex = ft_alloc_get_arena_index_by_size_request(size);
	if (aindex != arena->aindex || (chunk = ft_alloc_search_chunk_by_address(arena, ptr)) == NULL)
		return (EXIT_FAILURE);
	if (size > chunk->size)
	{
		ft_alloc_chunk_concat(arena, chunk);
		ptr = (void *)((FT_AUINT)chunk + g_alloc.info.size_chunk);
	}
	ft_alloc_chunk_split(arena, chunk, size);
	if (chunk->next != NULL)
		ft_alloc_chunk_concat(arena, chunk->next);
	if (size > chunk->size)
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

static void		*ft_realloc_by_mmap(t_aarena *arena, void *ptr, size_t size)
{
	t_achunk	*chunk;
	void		*new;

	new = NULL;
	// if ((chunk = ft_alloc_search_chunk_by_address(arena, ptr)) == NULL)
	// 	return (NULL);
	// ft_alloc_pthread_lock_by_parent();
	// new = malloc(size);
	// ft_alloc_pthread_unlock_by_parent();
	// if (new == NULL)
	// 	return (NULL);
	// ft_alloc_memcpy(new, ptr, (chunk->size >= size) ? size : chunk->size);
	// ft_alloc_pthread_lock_by_parent();
	// free(ptr);
	// ft_alloc_pthread_unlock_by_parent();
	return (new);
}

static void			*ft_realloc(void *ptr, size_t size)
{
	void		*new;
	t_aarena	**arena;

	new = NULL;
	arena = NULL;
	size = ft_alloc_get_size_aligned(size, FT_AALIGNMENT);
	if (ptr == NULL)
	{
		ft_alloc_pthread_lock_by_parent();
		new = malloc(size);
		ft_alloc_pthread_unlock_by_parent();
	}
	else if ((arena = ft_alloc_search_arena_by_address(ptr)) != NULL)
	{
		// if (ft_realloc_by_concat(*arena, ptr, size) == EXIT_SUCCESS)
		// 	new = ptr;
		// else
			new = ft_realloc_by_mmap(*arena, ptr, size);
	}

	return (new);
}

void			*realloc(void *ptr, size_t size)
{
	void		*new;

	new = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return (NULL);
	if (g_alloc.info.pagesize != 0 || ft_alloc_init() == EXIT_SUCCESS)
		new = ft_realloc(ptr, size);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return (NULL);
	return (new);
}
