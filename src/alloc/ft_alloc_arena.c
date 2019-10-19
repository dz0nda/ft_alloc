/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_arena.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/05 03:42:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 04:54:34 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"
#include "../show/ft_show.h"

static size_t	ft_alloc_get_map_size_by_size_request(size_t size)
{
	t_ainfo		info;

	ft_alloc_memcpy(&info, &g_alloc.info, sizeof(t_ainfo));
	if (size <= info.tiny_size_request)
		return (info.tiny_size_map);
	else if (size > info.tiny_size_request && size <= info.small_size_request)
		return (info.small_size_map);
	return (ft_alloc_size_aligned((size + info.size_arena + info.size_chunk), info.pagesize));
}

t_achunk		*ft_alloc_arena_new(size_t size)
{
	size_t		size_map;
	t_aarena	**last;
	t_aarena	*new;

	size_map = ft_alloc_get_map_size_by_size_request(size);
	last = ft_alloc_get_arena_by_size_request(size);
	if ((new = (t_aarena *)mmap(NULL, size_map,
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	ft_alloc_memset(new, 0, sizeof(t_aarena));
	new->size = size_map;
	new->aindex = ft_alloc_get_arena_index_by_size_request(size);
	new->head = (t_achunk *)((FT_AUINT)new + g_alloc.info.size_arena);
	new->head->size = size_map - g_alloc.info.size_arena - g_alloc.info.size_chunk;
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
	if ((*arena)->size == (chunk->size + g_alloc.info.size_arena + g_alloc.info.size_chunk))
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
