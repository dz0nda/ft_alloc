/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alloc_arena.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/05 03:42:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 07:53:05 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "alloc.h"

static void		ft_alloc_arena_del_delete(t_aarena **arena, t_aarena *del)
{
	if (*arena == NULL || del == NULL)
		return ;
	if (del->prev == NULL)
		*arena = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
}

static void		ft_alloc_arena_new_append(t_aarena **arena, t_aarena *new)
{
	t_aarena	*last;

	last = *arena;
	if (*arena == NULL)
	{
		new->prev = NULL;
		*arena = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}

static t_aarena	*ft_alloc_arena_new_mmap(size_t size)
{
	t_aarena	*new;
	size_t		size_map;

	new = NULL;
	size_map = ft_alloc_get_map_size_by_size_request(size);
	if ((new = (t_aarena *)mmap(NULL, size_map,
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	new->size = size_map;
	new->aindex = ft_alloc_get_arena_index_by_size_request(size);
	new->head = (t_achunk *)(new + 1);
	new->head->size = size_map - g_alloc.info.size_arena - g_alloc.info.size_chunk;
	new->head->free = TRUE;
	new->head->prev = new->head;
	new->head->next = new->head;
	new->next = NULL;
	return (new);
}

t_achunk		*ft_alloc_arena_new(t_aarena **arena, size_t size)
{
	t_aarena	*new;

	new = NULL;
	if ((new = ft_alloc_arena_new_mmap(size)) == NULL)
		return (NULL);
	ft_alloc_arena_new_append(arena, new);
	ft_alloc_state_mmap(new->aindex, new->size, TRUE);
	ft_alloc_state_freed(new->aindex, new->head->size, TRUE);
	ft_alloc_state_ovhead(new->aindex, (g_alloc.info.size_arena + g_alloc.info.size_chunk), FALSE);
	ft_alloc_state_nbrarenas(new->aindex, TRUE);
	ft_alloc_state_nbrchunks(new->aindex, TRUE);
	return (new->head);
}

int				ft_alloc_arena_del(t_aarena **arena)
{
	t_aarena	*del;

	del = *arena;
	ft_alloc_state_mmap(del->aindex, del->size, FALSE);
	ft_alloc_state_freed(del->aindex, del->head->size, FALSE);
	ft_alloc_state_ovhead(del->aindex, (g_alloc.info.size_arena + g_alloc.info.size_chunk), TRUE);
	ft_alloc_state_nbrarenas(del->aindex, FALSE);
	ft_alloc_state_nbrchunks(del->aindex, FALSE);
	ft_alloc_arena_del_delete(arena, del);
	if (munmap((void *)(del), del->size) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
