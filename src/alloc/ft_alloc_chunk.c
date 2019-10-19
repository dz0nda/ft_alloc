/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_chunk.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:05:40 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 06:20:40 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

t_achunk		*ft_alloc_chunk_concat(t_achunk *chunk)
{
	if ((chunk->next != NULL) && (chunk->next->free == FT_TRUE))
	{
		chunk->size += chunk->next->size + g_alloc.info.size_chunk;
		if ((chunk->next = chunk->next->next) != NULL)
			chunk->next->prev = chunk;
	}
	if ((chunk->prev != NULL) && (chunk->prev->free == FT_TRUE))
	{
		chunk->prev->size += chunk->size + g_alloc.info.size_chunk;
		if ((chunk->prev->next = chunk->next) != NULL)
			chunk->next->prev = chunk->prev;
		chunk = chunk->prev;
	}
	return (chunk);
}

t_achunk		*ft_alloc_chunk_split(t_achunk *chunk, size_t size)
{
	t_achunk	*new;

	new = NULL;
	if (size > g_alloc.info.small_size_request || !(chunk->size > (size + g_alloc.info.size_chunk)))
		return (chunk);
	new = (t_achunk *)((FT_AUINT)chunk + g_alloc.info.size_chunk + size);
	new->size = chunk->size - (g_alloc.info.size_chunk + size);
	new->free = FT_TRUE;
	new->next = chunk->next;
	if (new->next != NULL)
		new->next->prev = new;
	new->prev = chunk;
	chunk->size = size;
	chunk->next = new;
	return (chunk);
}
