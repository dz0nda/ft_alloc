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

static int		ft_alloc_chunk_concat_info(t_aindex aindex, t_achunk *chunk)
{
	if (chunk->free == FALSE)
	{
		ft_alloc_state_used(aindex, g_alloc.info.size_chunk, FALSE);
		ft_alloc_state_ovhead(aindex, g_alloc.info.size_chunk, TRUE);
		ft_alloc_state_swap(aindex, chunk->size, FALSE);
	}
	else
	{
		ft_alloc_state_freed(aindex, g_alloc.info.size_chunk, TRUE);
		ft_alloc_state_ovhead(aindex, g_alloc.info.size_chunk, TRUE);
	}
	ft_alloc_state_nbrchunks(aindex, FALSE);
	return (EXIT_SUCCESS);
}

static int		ft_alloc_chunk_split_info(t_aindex aindex, t_achunk *chunk, size_t size)
{
	if (size > g_alloc.info.small_size_request || !(chunk->size > (size + g_alloc.info.size_chunk)))
		return (EXIT_FAILURE);
	if (chunk->free == FALSE)
	{
		ft_alloc_state_used(aindex, g_alloc.info.size_chunk, TRUE);
		ft_alloc_state_ovhead(aindex, g_alloc.info.size_chunk, FALSE);
		ft_alloc_state_swap(aindex, chunk->size - (g_alloc.info.size_chunk + size), TRUE);
	}
	else
	{
		ft_alloc_state_freed(aindex, g_alloc.info.size_chunk, FALSE);
		ft_alloc_state_ovhead(aindex, g_alloc.info.size_chunk, FALSE);
	}
	ft_alloc_state_nbrchunks(aindex, TRUE);
	return (EXIT_SUCCESS);
}

int				ft_alloc_chunk_concat(t_aarena *arena, t_achunk *chunk)
{
	FT_ALLOC_UINT	size_chunk;
	FT_ALLOC_UINT	addr_chunkh;
	FT_ALLOC_UINT	addr_prevh;

	size_chunk = g_alloc.info.size_chunk;
	addr_chunkh = (FT_ALLOC_UINT)chunk + size_chunk;
	addr_prevh = (FT_ALLOC_UINT)chunk->prev + size_chunk;
	if ((chunk->next->free == TRUE) && (chunk->next > chunk))
	{
		ft_alloc_chunk_concat_info(arena->aindex, chunk);
		chunk->size += chunk->next->size + size_chunk;
		chunk->next = chunk->next->next;
		chunk->next->prev = chunk;
	}
	if ((chunk->prev->free == TRUE) && (chunk->prev < chunk))
	{
		ft_alloc_chunk_concat_info(arena->aindex, chunk);
		chunk->prev->size += chunk->size + size_chunk;
		chunk->prev->free = chunk->free;
		chunk->prev->next = chunk->next;
		chunk->next->prev = chunk->prev;
		ft_alloc_chunk_copy((void *)(addr_prevh), (void *)(addr_chunkh), chunk->size);
		chunk = chunk->prev;
	}
	return (EXIT_SUCCESS);
}

void			*ft_alloc_chunk_copy(void *dest, const void *src, size_t n)
{
	char		*d;
	char		*s;

	d = (char *)dest;
	s = (char *)src;
	while (n-- > 0)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
}

int				ft_alloc_chunk_split(t_aarena *arena, t_achunk *chunk, size_t size)
{
	t_achunk	*new;

	new = NULL;
	if (ft_alloc_chunk_split_info(arena->aindex, chunk, size) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	new = (t_achunk *)((FT_ALLOC_UINT)chunk + g_alloc.info.size_chunk + size);
	new->size = chunk->size - (g_alloc.info.size_chunk + size);
	new->free = TRUE;
	chunk->size = size;
	new->next = chunk->next;
	new->prev = chunk;
	chunk->next->prev = new;
	chunk->next = new;
	return (EXIT_SUCCESS);
}