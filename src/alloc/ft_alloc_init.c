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
	FT_AUINT	size_map;

	ft_alloc_memset(&rlp, 0, sizeof(t_limit));
	info = &(g_alloc).info;
	size_map = 0;
	if (getrlimit(RLIMIT_AS, &rlp) == -1)
		return (EXIT_FAILURE);
	info->rlim_cur = (FT_AUINT)rlp.rlim_cur;
	info->rlim_max = (FT_AUINT)rlp.rlim_max;
	info->size_chunk = ft_alloc_get_size_aligned(sizeof(t_achunk), FT_AALIGNMENT);
	info->size_arena = ft_alloc_get_size_aligned(sizeof(t_aarena), FT_AALIGNMENT);
	if ((info->pagesize = getpagesize()) == 0)
		return (EXIT_FAILURE);
	info->tiny_size_request = ft_alloc_get_size_aligned(FT_ATINY, FT_AALIGNMENT);
	info->small_size_request = ft_alloc_get_size_aligned(FT_ASMALL, FT_AALIGNMENT);
	size_map = (info->tiny_size_request * FT_AN) + (info->size_chunk * (FT_AN)) + info->size_arena;
	info->tiny_size_map = ft_alloc_get_size_aligned(size_map, info->pagesize);
	size_map = (info->small_size_request * FT_AM) + (info->size_chunk * (FT_AM)) + info->size_arena;
	info->small_size_map = ft_alloc_get_size_aligned(size_map, info->pagesize);
	return (EXIT_SUCCESS);
}

int					ft_alloc_init(void)
{
	if (ft_alloc_init_info() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
