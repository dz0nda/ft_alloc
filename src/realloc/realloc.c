/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:37:50 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 07:58:05 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "realloc.h"

static int		ft_realloc_by_concat(t_aarena *arena, void *ptr, size_t size)
{
	t_achunk	*node;
	t_aindex	aindex;

	node = NULL;
	aindex = ft_alloc_get_arena_index_by_size_request(size);
	if ((aindex != arena->aindex) || ((node = ft_alloc_search_chunk_by_address(arena, ptr)) == NULL))
		return (EXIT_FAILURE);
	if (size > node->size)
	{
		ft_alloc_chunk_concat(arena, node);
		ptr = (void *)((FT_ALLOC_UINT)node + g_alloc.info.size_chunk);
	}
	ft_alloc_chunk_split(arena, node, size);
	ft_alloc_chunk_concat(arena, node->next);
	if (size > node->size)
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
	pthread_mutex_lock(&g_mutex);
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
	pthread_mutex_unlock(&g_mutex);
	return (new);
}
