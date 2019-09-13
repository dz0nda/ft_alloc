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

static void		ft_alloc_arena_append(t_anode **head, t_anode *new)
{
	if (*head == NULL) 
	{
		new->prev = new; 
		new->next = new; 
		*head = new; 
	}
	else
	{
		(*head)->prev->next = new;
		new->prev = (*head)->prev; 
		new->next = *head; 
		(*head)->prev = new; 
	}
}

static t_anode *ft_alloc_arena_mmap(size_t size)
{
		t_anode *new;
		size_t	size_arena;

		new = NULL;
		size_arena = ft_alloc_get_arena_size_by_size(size);
		if ((new = (t_anode *)mmap(NULL, size_arena,
		PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) == MAP_FAILED)
			return (NULL);
		new->size = size_arena - FT_ALLOC_SIZE_META;
		new->free = TRUE;
		return (new);
}

t_anode 	*ft_alloc_arena(size_t size) 
{ 
	t_anode *new;
	t_anode **head;

	new = NULL;
	head = ft_alloc_get_arena_by_size(size);
	// if (ft_alloc_info_mmap(size, FALSE) == EXIT_FAILURE)
	// 	return (NULL);
	if ((new = ft_alloc_arena_mmap(size)) == NULL)
		return (NULL);
	ft_alloc_arena_append(head, new);
	ft_alloc_info_address((FT_ALLOC_UINT)new, size);
	return (new);
}