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

static void		ft_alloc_arena_mmap_append(t_aarena **arena, t_aarena *new)
{
	t_aarena 		*last;

	last = *arena;
	if (*arena == NULL)
	{
		*arena = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return ;
}

t_achunk 		*ft_alloc_arena_mmap(t_aarena **arena, size_t size) 
{ 
	t_aarena 	*new;
	size_t 		size_arena;

	new = NULL;
	size_arena = ft_alloc_get_arena_size_by_size(size);
	if (ft_alloc_info_mmap(size_arena, TRUE) == EXIT_FAILURE)
	 	return (NULL);
	if ((new = (t_aarena *)mmap(NULL, size_arena,
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	new->size = size_arena;
	new->head = (t_achunk *)(new + 1);
	new->head->size = size_arena - (FT_ALLOC_SIZE_ARENA + FT_ALLOC_SIZE_CHUNK);
	new->head->free = TRUE;
	new->head->prev = new->head;
	new->head->next = new->head;
	ft_alloc_arena_mmap_append(arena, new);
	ft_alloc_info_freed(*arena, new->head->size, TRUE);
	return (new->head);
}