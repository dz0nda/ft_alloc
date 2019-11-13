/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:36:54 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 21:15:03 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_free.h"

static void		ft_free(void *ptr)
{
	t_achunk	*chunk;

	chunk = NULL;
	if (ptr == NULL || ((chunk = ft_alloc_search_chunk_by_address(ptr)) == NULL))
		return ;
	chunk->free = FT_TRUE;
	ft_alloc_history(chunk, FT_FREE);
	ft_alloc_chunk_concat(chunk);
	ft_alloc_arena_del(chunk);
}

void			free(void *ptr)
{
	if (pthread_mutex_lock(&g_mutex) != 0)
		return ;
	if (ft_alloc_init() == EXIT_SUCCESS)
		ft_free(ptr);
	if (pthread_mutex_unlock(&g_mutex) != 0)
		return ;
}
