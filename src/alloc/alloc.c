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

int		ft_alloc_arena_split(t_node *node, size_t size)
{
	t_node *new;

	new = NULL;
	new = (t_node *)((FT_ALLOC_UINT)node + FT_ALLOC_SIZE_NODE + size);
	new->size = node->size - (FT_ALLOC_SIZE_NODE + size);
	new->free = TRUE;
	node->size = size;
	new->next = node->next;
	new->prev = node;
	node->next->prev = new;
	node->next = new;
	return (EXIT_SUCCESS);
}

int 	ft_alloc_arena(t_node **head, size_t size) 
{ 
    t_node*		new;

		new = NULL;
		if ((new = (t_node *)mmap(NULL, size,
		PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) == MAP_FAILED)
			return (EXIT_FAILURE);
		new->size = size - FT_ALLOC_SIZE_NODE;
		new->free = TRUE;
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
		return (EXIT_SUCCESS);
}