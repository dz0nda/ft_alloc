/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_state_user.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:07:42 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/23 21:11:11 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

int				ft_alloc_state_freed(t_aindex aindex, size_t size, t_bool free)
{
	t_astate	*state;

	state = &(g_alloc).state;
	if (free == FT_TRUE)
		state->freed[aindex] += size;
	else
		state->freed[aindex] -= size;
	return (EXIT_SUCCESS);
}

int				ft_alloc_state_swap(t_aindex aindex, size_t size, t_bool free)
{
	t_astate	*state;

	state = &(g_alloc).state;
	if (free == FT_TRUE)
	{
		state->freed[aindex] += size;
		state->used[aindex] -= size;
	}
	else
	{
		state->freed[aindex] -= size;
		state->used[aindex] += size;
	}
	return (EXIT_SUCCESS);
}

int				ft_alloc_state_used(t_aindex aindex, size_t size, t_bool free)
{
	t_astate	*state;

	state = &(g_alloc).state;
	if (free == FT_TRUE)
		state->used[aindex] -= size;
	else
		state->used[aindex] += size;
	return (EXIT_SUCCESS);
}
