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

t_anode 	*ft_alloc_arena_new_by_size(size_t size) 
{ 
	t_anode *new;
	t_anode **head;
	size_t	size_arena;

	new = NULL;
	head = ft_alloc_get_arena_by_size(size);
	size_arena = ft_alloc_get_arena_size_by_size(size);
	if (ft_alloc_info_mmap(size, FALSE) == EXIT_FAILURE)
		return (NULL);
	if ((new = (t_anode *)mmap(NULL, size_arena,
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	new->size = size_arena - FT_ALLOC_SIZE_META;
	new->free = TRUE;
	ft_alloc_arena_append(head, new);
		ft_alloc_info_address((FT_ALLOC_UINT)new, size);
	return (*head);
}

int		ft_alloc_arena_split(t_anode *node, size_t size)
{
	t_anode *new;

	new = NULL;
	if (!(node->size > (size + FT_ALLOC_SIZE_META + FT_ALLOC_ALIGNMENT)))
		return (EXIT_FAILURE);
	new = (t_anode *)((FT_ALLOC_UINT)node + FT_ALLOC_SIZE_META + size);
	new->size = node->size - (FT_ALLOC_SIZE_META + size);
	new->free = TRUE;
	node->size = size;
	new->next = node->next;
	new->prev = node;
	node->next->prev = new;
	node->next = new;
	return (EXIT_SUCCESS);
}

int     ft_alloc_arena_concat(t_anode *node)
{
    FT_ALLOC_UINT addr_prev;
    FT_ALLOC_UINT addr_next;

    addr_prev = (FT_ALLOC_UINT)node->prev;
    addr_next = (FT_ALLOC_UINT)node->next;
    if ((node->prev->free == TRUE) && (node->prev < node))
    {
        node->prev->size += node->size + FT_ALLOC_SIZE_META;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node = node->prev;
        ft_alloc_info_free(FT_ALLOC_SIZE_META, TRUE);
    }
    if ((node->next->free == TRUE) && (node->next > node))
    {
        node->size += node->next->size + FT_ALLOC_SIZE_META;
        node->next = node->next->next;
        node->next->prev = node;
        ft_alloc_info_free(FT_ALLOC_SIZE_META, TRUE);
    }
    return (EXIT_SUCCESS);
}
