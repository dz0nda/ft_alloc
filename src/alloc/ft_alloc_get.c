/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_get.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:08:39 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/23 21:10:58 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

t_aarena		**ft_alloc_get_arena_by_size_request(size_t size)
{
	t_ainfo		info;
	t_astate	*state;

	info = g_alloc.info;
	state = &(g_alloc).state;
	if (size <= info.tiny_size_request)
		return (&(state->arena)[ALLOC_TINY]);
	else if (size > info.tiny_size_request && size <= info.small_size_request)
		return (&(state->arena)[ALLOC_SMALL]);
	return (&(state->arena)[ALLOC_LARGE]);
}

t_aindex		ft_alloc_get_arena_index_by_size_request(size_t size)
{
	t_ainfo		info;

	info = g_alloc.info;
	if (size <= info.tiny_size_request)
		return (ALLOC_TINY);
	else if (size > info.tiny_size_request && size <= info.small_size_request)
		return (ALLOC_SMALL);
	return (ALLOC_LARGE);
}

size_t			ft_alloc_get_map_size_by_size_request(size_t size)
{
	t_ainfo		info;

	info = g_alloc.info;
	if (size <= info.tiny_size_request)
		return (info.tiny_size_map);
	else if (size > info.tiny_size_request && size <= info.small_size_request)
		return (info.small_size_map);
	return (ft_alloc_get_size_aligned((size + info.size_arena + info.size_chunk), info.pagesize));
}

size_t			ft_alloc_get_size_aligned(size_t offset, size_t align)
{
	return ((offset % align == 0) ? offset : offset + (align - (offset % align) % align));
}
