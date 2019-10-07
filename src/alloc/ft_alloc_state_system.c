/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_state_system.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:07:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/23 21:11:09 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

int				ft_alloc_state_mmap(t_aindex aindex, size_t size, t_bool mmap)
{
	t_astate	*state;

	state = &(g_alloc).state;
	if (mmap == FT_TRUE)
		state->mmap[aindex] += size;
	else
		state->mmap[aindex] -= size;
	return (EXIT_SUCCESS);
}

int				ft_alloc_state_nbrarenas(t_aindex aindex, t_bool add)
{
	t_astate	*state;

	state = &(g_alloc).state;
	if (add == FT_TRUE)
		state->nbrarenas[aindex] += 1;
	else
		state->nbrarenas[aindex] -= 1;
	return (EXIT_SUCCESS);
}

int				ft_alloc_state_nbrchunks(t_aindex aindex, t_bool add)
{
	t_astate	*state;

	state = &(g_alloc).state;
	if (add == FT_TRUE)
		state->nbrchunks[aindex] += 1;
	else
		state->nbrchunks[aindex] -= 1;
	return (EXIT_SUCCESS);
}
