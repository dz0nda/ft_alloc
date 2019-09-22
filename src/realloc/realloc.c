/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:37:50 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/22 06:34:31 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "realloc.h"

static int		ft_realloc_by_concat(t_aarena *arena, void *ptr, size_t size)
{
	t_achunk	*chunk;
	t_aindex	aindex;

	chunk = NULL;
	aindex = ft_alloc_get_arena_index_by_size_request(size);
	if ((aindex != arena->aindex) || ((chunk = ft_alloc_search_chunk_by_address(arena, ptr)) == NULL))
		return (EXIT_FAILURE);
	if (size > chunk->size)
	{
		ft_alloc_chunk_concat(arena, chunk);
		ptr = (void *)((FT_ALLOC_UINT)chunk + g_alloc.info.size_chunk);
	}
	ft_alloc_chunk_split(arena, chunk, size);
	ft_alloc_chunk_concat(arena, chunk->next);
	if (size > chunk->size)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void		*ft_realloc_by_mmap(t_aarena *arena, void *ptr, size_t size)
{
	t_achunk	*chunk;
	void		*new;

	if ((chunk = ft_alloc_search_chunk_by_address(arena, ptr)) == NULL)
		return (NULL);
	if ((new = malloc(size)) == NULL)
		return (NULL);
	ft_alloc_chunk_copy(new, ptr, (chunk->size >= size) ? size : chunk->size);
	free(ptr);
	return (new);
}

void			*realloc(void *ptr, size_t size)
{
	t_aarena	**arena;
	void		*new;

	arena = NULL;
	new = NULL;
	if (ft_alloc_init_pthread_new() == EXIT_FAILURE)
		return (NULL);
	if (g_alloc.info.pagesize != 0 || ft_alloc_init() == EXIT_SUCCESS)
	{
		size = ft_alloc_get_size_aligned(size, FT_ALLOC_ALIGNMENT);
		if (ptr == NULL)
			new = malloc(size);
		else
		{
			if ((arena = ft_alloc_search_arena_by_address(ptr)) != NULL)
			{
				if ((ft_realloc_by_concat(*arena, ptr, size)) == EXIT_SUCCESS)
					new = ptr;
				else
					new = ft_realloc_by_mmap(*arena, ptr, size);
			}
		}
	}
	if (ft_alloc_init_pthread_del() == EXIT_FAILURE)
		return (NULL); 
	return (new);
}
