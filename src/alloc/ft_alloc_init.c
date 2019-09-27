/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_init.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:08:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 01:51:39 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

t_alloc				g_alloc;
t_mutex				g_mutex;

static int			ft_alloc_init_info(void)
{
	t_limit			rlp;
	t_ainfo			*info;
	FT_ALLOC_UINT	size_map;

	ft_alloc_memset(&rlp, 0, sizeof(t_limit));
	info = &(g_alloc).info;
	size_map = 0;
	if (getrlimit(RLIMIT_MEMLOCK, &rlp) == -1)
		return (EXIT_FAILURE);
	info->rlim_cur = (FT_ALLOC_UINT)rlp.rlim_cur;
	info->rlim_max = (FT_ALLOC_UINT)rlp.rlim_max;
	info->size_chunk = ft_alloc_get_size_aligned(sizeof(t_achunk), FT_ALLOC_ALIGNMENT);
	info->size_arena = ft_alloc_get_size_aligned(sizeof(t_aarena), FT_ALLOC_ALIGNMENT);
	if ((info->pagesize = getpagesize()) == 0)
		return (EXIT_FAILURE);
	info->tiny_size_request = ft_alloc_get_size_aligned(FT_ALLOC_TINY, FT_ALLOC_ALIGNMENT);
	info->small_size_request = ft_alloc_get_size_aligned(FT_ALLOC_SMALL, FT_ALLOC_ALIGNMENT);
	size_map = (info->tiny_size_request * FT_ALLOC_N) + (info->size_chunk * (FT_ALLOC_N)) + info->size_arena;
	info->tiny_size_map = ft_alloc_get_size_aligned(size_map, info->pagesize);
	size_map = (info->small_size_request * FT_ALLOC_M) + (info->size_chunk * (FT_ALLOC_M)) + info->size_arena;
	info->small_size_map = ft_alloc_get_size_aligned(size_map, info->pagesize);
	return (EXIT_SUCCESS);
}

int					ft_alloc_init(void)
{
	if (ft_alloc_init_info() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
