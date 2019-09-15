/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alloc.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/05 03:42:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/05 03:46:06 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "alloc.h"

static void		ft_alloc_arena_del_delete(t_aarena *arena, t_aarena *del)
{

	if (arena == NULL || del == NULL)
		return ;
	if (del->prev == NULL)
		arena = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next;
}

static void		ft_alloc_arena_new_append(t_aarena **arena, t_aarena *new)
{
	t_aarena 		*last;

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

static t_aarena		*ft_alloc_arena_new_mmap(size_t size)
{
	t_aarena 	*new;
	size_t 		size_arena;

	new = NULL;
	size_arena = ft_alloc_get_arena_size_by_size_request(size);
	if ((new = (t_aarena *)mmap(NULL, size_arena,
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	new->size = size_arena;
	new->aindex = ft_alloc_get_arena_index_by_size_request(size);
	new->head = (t_achunk *)((FT_ALLOC_UINT)new + g_alloc.info.size_arena);
	new->head->size = size_arena - g_alloc.info.size_arena;
	new->head->free = TRUE;
	new->head->prev = new->head;
	new->head->next = new->head;
	return (new);
}

t_achunk 		*ft_alloc_arena_new(t_aarena **arena, size_t size) 
{ 
	t_aarena 	*new;

	new = NULL;
	if ((new = ft_alloc_arena_new_mmap(size)) == NULL)
		return (NULL);
	ft_alloc_arena_new_append(arena, new);
	ft_alloc_state_mmap(new->aindex, new->size, TRUE);
	ft_alloc_state_freed(new->aindex, new->head->size, TRUE);
	ft_alloc_state_ovhead(new->aindex, g_alloc.info.size_arena, FALSE);
	return (new->head);
}

int					ft_alloc_arena_del(t_aarena *arena) 
{ 
	t_aarena 	*del;

	del = arena;
	ft_alloc_state_mmap(del->aindex, del->size, FALSE);
	ft_alloc_state_freed(del->aindex, del->head->size, FALSE);
	ft_alloc_state_ovhead(del->aindex, g_alloc.info.size_arena, TRUE);
	ft_alloc_arena_del_delete(arena, del);
	if (munmap((void *)(del), del->size) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}