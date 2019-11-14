/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_arena.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/05 03:42:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 06:53:26 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

static size_t	ft_alloc_get_map_size_by_size_request(size_t size)
{
	t_ainfo		info;

	ft_memcpy(&info, &g_alloc.info, sizeof(t_ainfo));
	if (size <= info.s_tiny_request)
		return (info.s_tiny_map);
	else if (size > info.s_tiny_request && size <= info.s_small_request)
		return (info.s_small_map);
	return (ft_alloc_align_size((size + info.s_arena + info.s_chunk),
				info.s_page));
}

t_aarena		**ft_alloc_get_arena_by_size(size_t size)
{
	t_ainfo		info;

	ft_memcpy(&info, &g_alloc.info, sizeof(t_ainfo));
	if (size <= info.s_tiny_request)
		return (&g_alloc.arena[FT_ALLOC_TINY]);
	else if (size > info.s_tiny_request && size <= info.s_small_request)
		return (&g_alloc.arena[FT_ALLOC_SMALL]);
	return (&g_alloc.arena[FT_ALLOC_LARGE]);
}

t_aindex		ft_alloc_get_aindex_by_size(size_t size)
{
	t_ainfo		info;

	ft_memcpy(&info, &g_alloc.info, sizeof(t_ainfo));
	if (size <= info.s_tiny_request)
		return (FT_ALLOC_TINY);
	else if (size > info.s_tiny_request && size <= info.s_small_request)
		return (FT_ALLOC_SMALL);
	return (FT_ALLOC_LARGE);
}

t_achunk		*ft_alloc_arena_new(size_t size)
{
	size_t		size_map;
	t_aarena	**last;
	t_aarena	*new;

	size_map = ft_alloc_get_map_size_by_size_request(size);
	last = ft_alloc_get_arena_by_size(size);
	if ((new = (t_aarena *)mmap(NULL, size_map,
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	ft_memset(new, 0, sizeof(t_aarena));
	new->size = size_map;
	new->aindex = ft_alloc_get_aindex_by_size(size);
	new->head = (t_achunk *)((FT_AUINT)new + g_alloc.info.s_arena);
	new->head->size = size_map - g_alloc.info.s_arena - g_alloc.info.s_chunk;
	if (*last == NULL)
		*last = new;
	else
	{
		while ((*last)->next != NULL)
			last = &(*last)->next;
		(*last)->next = new;
		new->prev = *last;
	}
	return (new->head);
}

int				ft_alloc_arena_del(t_achunk *chunk)
{
	t_aarena **arena;
	t_aarena *del;

	if ((arena = ft_alloc_search_arena_by_address((void *)chunk)) == NULL)
		return (EXIT_FAILURE);
	del = (*arena);
	if ((del->prev != NULL || del->next != NULL) && ((*arena)->size ==
		(chunk->size + g_alloc.info.s_arena + g_alloc.info.s_chunk)))
	{
		if (del->prev == NULL)
			*arena = del->next;
		if (del->next != NULL)
			del->next->prev = del->prev;
		if (del->prev != NULL)
			del->prev->next = del->next;
		if (munmap((void *)(del), del->size) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
