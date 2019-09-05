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

t_allocinfo		g_allocinfo = { { NULL } };

int		ft_alloc_split_node(t_node *node, size_t size)
{
	t_node *next;

	next = NULL;
	next = node->next;
	node->next = (t_node *)((FT_ALLOC_UINT)node + FT_ALLOC_SIZE_NODE + size);
	node->next->size = node->size - (FT_ALLOC_SIZE_NODE + size);
	node->next->free = TRUE;
	node->next->next = next;
	return (EXIT_SUCCESS);
}

int		ft_alloc_arena(t_node **head, size_t size)
{
	t_node	*new;
	t_node	*last;

	new = NULL;
	last = NULL;
	if ((new = (t_node *)mmap(NULL, size,
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (EXIT_FAILURE);
	last = *head;
	new->size = size - FT_ALLOC_SIZE_NODE;
	new->free = TRUE;
	new->next = NULL;
	if (*head == NULL)
	{
		new->prev = NULL;
		*head = new;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
	return (EXIT_SUCCESS);
}
