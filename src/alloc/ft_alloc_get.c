/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_get.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/24 06:14:33 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 19:33:03 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

t_aarena		**ft_alloc_get_arena_by_size_request(size_t size)
{
	t_ainfo		info;

	ft_alloc_memcpy(&info, &g_alloc.info, sizeof(t_ainfo));
	if (size <= info.tiny_size_request)
		return (&g_alloc.arena[FT_ALLOC_TINY]);
	else if (size > info.tiny_size_request && size <= info.small_size_request)
		return (&g_alloc.arena[FT_ALLOC_SMALL]);
	return (&g_alloc.arena[FT_ALLOC_LARGE]);
}

t_aindex		ft_alloc_get_arena_index_by_size_request(size_t size)
{
	t_ainfo		info;

	ft_alloc_memcpy(&info, &g_alloc.info, sizeof(t_ainfo));
	if (size <= info.tiny_size_request)
		return (FT_ALLOC_TINY);
	else if (size > info.tiny_size_request && size <= info.small_size_request)
		return (FT_ALLOC_SMALL);
	return (FT_ALLOC_LARGE);
}

size_t			ft_alloc_size_aligned(size_t offset, size_t align)
{
	return ((offset % align == 0) ? offset : offset + (align - (offset % align) % align));
}
