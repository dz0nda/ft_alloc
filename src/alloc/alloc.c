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

int 	ft_alloc_arena(t_anode **head, size_t size) 
{ 
    t_anode *new;

		new = NULL;
		ft_ainfo_mmap(ft_alloc_get_target(size), ft_alloc_get_size_arena(size), FALSE);
		size = ft_alloc_get_size_arena(size);
//		ft_ainfo_rall_mmap(ALLOC_NONE, size, FALSE);
		if ((new = (t_anode *)mmap(NULL, size,
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


int		ft_alloc_init(void)
{
  t_alloc_info  *alloc_info;
  struct rlimit rlp;

	ft_memset(&rlp, 0, sizeof(struct rlimit));
  alloc_info = &(g_alloc_state).alloc_info;
  if (alloc_info->rlim_cur == 0 && alloc_info->rlim_max == 0)
    if (getrlimit(RLIMIT_MEMLOCK, &rlp) == -1)
      return (ft_alloc_error(AE_INIT));
  alloc_info->rlim_cur = rlp.rlim_cur;
  alloc_info->rlim_max = rlp.rlim_max;
  return (EXIT_SUCCESS);
}