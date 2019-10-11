/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_hist.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 21:01:50 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 21:02:01 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

void			ft_alloc_history(t_achunk *chunk, t_aindex index, t_alloc_ft aft)
{
	int			i;
	t_ahist		*history;
	t_ahist		newhistory;
	t_ahist		nexthistory;

	i = -1;
	history = g_alloc.history;
	newhistory.addr = (FT_AUINT)chunk + sizeof(t_achunk);
	newhistory.size = chunk->size;
	newhistory.free = chunk->free;
	newhistory.index = index;
	newhistory.aft = aft;
	while (++i < FT_AHIST)
	{
		ft_alloc_memcpy(&nexthistory, &history[i], sizeof(t_ahist));
		ft_alloc_memcpy(&history[i], &newhistory, sizeof(t_ahist));
		ft_alloc_memcpy(&newhistory, &nexthistory, sizeof(t_ahist));
	}
}
