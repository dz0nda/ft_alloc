/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_chunk.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/14 06:52:45 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 06:52:50 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

t_achunk		*ft_alloc_chunk_concat(t_achunk *chunk)
{
	if ((chunk->next != NULL) && (chunk->next->free == FT_TRUE))
	{
		chunk->size += chunk->next->size + g_alloc.info.s_chunk;
		if ((chunk->next = chunk->next->next) != NULL)
			chunk->next->prev = chunk;
	}
	if ((chunk->prev != NULL) && (chunk->prev->free == FT_TRUE))
	{
		chunk->prev->size += chunk->size + g_alloc.info.s_chunk;
		if ((chunk->prev->next = chunk->next) != NULL)
			chunk->next->prev = chunk->prev;
		chunk->prev->free = chunk->free;
		chunk = chunk->prev;
	}
	return (chunk);
}

t_achunk		*ft_alloc_chunk_split(t_achunk *chunk, size_t size)
{
	t_achunk	*new;

	new = NULL;
	if (chunk->size <= (size + g_alloc.info.s_chunk))
		return (chunk);
	new = (t_achunk *)((FT_AUINT)chunk + g_alloc.info.s_chunk + size);
	new->size = chunk->size - (g_alloc.info.s_chunk + size);
	new->free = FT_TRUE;
	new->next = chunk->next;
	if (new->next != NULL)
		new->next->prev = new;
	new->prev = chunk;
	chunk->size = size;
	chunk->next = new;
	return (chunk);
}
