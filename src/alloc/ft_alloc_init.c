/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_init.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:08:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 21:04:02 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

t_alloc			g_alloc;
t_mutex			g_mutex;

static int 		ft_alloc_init_rlimit(t_ainfo *info)
{
	t_limit		rlp;

	ft_alloc_memset(&rlp, 0, sizeof(t_limit));
	if (getrlimit(RLIMIT_AS, &rlp) == -1)
		return (EXIT_FAILURE);
	info->rlim_cur = (FT_AUINT)rlp.rlim_cur;
	info->rlim_max = (FT_AUINT)rlp.rlim_max;
	return (EXIT_SUCCESS);
}

static int		ft_alloc_init_system(t_ainfo *info)
{
	if ((info->pagesize = getpagesize()) == 0)
		return (EXIT_FAILURE);
	info->size_chunk = ft_alloc_size_aligned(sizeof(t_achunk), FT_AALIGN);
	info->size_arena = ft_alloc_size_aligned(sizeof(t_aarena), FT_AALIGN);
	return (EXIT_SUCCESS);
}

static int		ft_alloc_init_size(t_ainfo *info)
{
	FT_AUINT	size_map;

	size_map = 0;
	info->tiny_size_request = ft_alloc_size_aligned(FT_ATINY, FT_AALIGN);
	info->small_size_request = ft_alloc_size_aligned(FT_ASMALL, FT_AALIGN);
	size_map = (info->tiny_size_request * 100)
				+ (info->size_chunk * 100) + info->size_arena;
	info->tiny_size_map = ft_alloc_size_aligned(size_map, info->pagesize);
	size_map = (info->small_size_request * 100)
				+ (info->size_chunk * 100) + info->size_arena;
	info->small_size_map = ft_alloc_size_aligned(size_map, info->pagesize);
	return (EXIT_SUCCESS);
}

int				ft_alloc_init(void)
{
	t_ainfo		*info;

	info = &g_alloc.info;
	if (ft_alloc_init_rlimit(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_alloc_init_system(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_alloc_init_size(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
