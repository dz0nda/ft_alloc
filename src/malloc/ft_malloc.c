/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_malloc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 21:15:55 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 21:16:00 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		*ft_malloc(size_t size)
{
	t_achunk	*chunk;

	chunk = NULL;
	size = ft_alloc_align_size(size, FT_AALIGN);
	if ((chunk = ft_alloc_search_chunk_by_size(size)) == NULL)
		if ((chunk = ft_alloc_arena_new(size)) == NULL)
			return (NULL);
	chunk = ft_alloc_chunk_split(chunk, size);
	chunk->free = FT_FALSE;
	return ((void *)((FT_AUINT)chunk + g_alloc.info.s_chunk));
}

void			*malloc(size_t size)
{
	void	*new;

	new = NULL;
	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	if (ft_alloc_init() == EXIT_SUCCESS)
		new = ft_malloc(size);
	if (pthread_mutex_unlock(&g_mutex) != 0)
		return (NULL);
	return (new);
}
