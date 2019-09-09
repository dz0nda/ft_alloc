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

t_alloc_state		g_alloc_state;

int		ft_alloc_arena_split(t_anode *node, size_t size)
{
	t_anode *new;

	new = NULL;
	new = (t_anode *)((FT_ALLOC_UINT)node + FT_ALLOC_SIZE_NODE + size);
	new->size = node->size - (FT_ALLOC_SIZE_NODE + size);
	new->free = TRUE;
	node->size = size;
	new->next = node->next;
	new->prev = node;
	node->next->prev = new;
	node->next = new;
	return (EXIT_SUCCESS);
}

void	ft_alloc_arena_append(t_anode **head, t_anode *new)
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

void		*ft_alloc_mmap(FT_ALLOC_UINT size)
{
	void	*anon;

	anon = NULL;
	if ((anon = (t_anode *)mmap(NULL, size,
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (anon);
}

t_anode 	*ft_alloc_arena_new(size_t size) 
{ 
	t_anode *new;
	t_anode **head;
	t_aarena arena;

	new = NULL;
	head = ft_alloc_get_arena_by_size(size);
	arena = ft_alloc_get_arena_index_by_size(size);
	size = ft_alloc_get_arena_size_by_size(size);
	if (ft_ainfo_mmap(arena, size, FALSE) == EXIT_FAILURE)
		return (NULL);
	if ((new = (t_anode *)ft_alloc_mmap(size)) == NULL)
		return (NULL);
	new->size = size - FT_ALLOC_SIZE_NODE;
	new->free = TRUE;
	ft_ainfo_raddr(arena, (FT_ALLOC_UINT)new);
	ft_alloc_arena_append(head, new);
	return (new);
}