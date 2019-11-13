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

t_alloc			g_alloc = { 0 };
t_mutex			g_mutex = PTHREAD_MUTEX_INITIALIZER;

static int		ft_alloc_init_info(void)
{
	t_limit		rl;
	t_ainfo  	*info;
	
	ft_memset(&rl, 0, sizeof(t_limit));
	if	((info = &g_alloc.info) == NULL)
		return (EXIT_FAILURE);
	if (getrlimit(RLIMIT_AS, &rl) == -1 || !(info->s_page = getpagesize()))
		return (EXIT_FAILURE);
	info->rlim_cur = (FT_AUINT)rl.rlim_cur;
	info->rlim_max = (FT_AUINT)rl.rlim_max;
	info->s_chunk = ft_alloc_align_size(sizeof(t_achunk), FT_AALIGN);
	info->s_arena = ft_alloc_align_size(sizeof(t_aarena), FT_AALIGN);
	info->s_tiny_request = ft_alloc_align_size(FT_ATINY, FT_AALIGN);
	info->s_small_request = ft_alloc_align_size(FT_ASMALL, FT_AALIGN);
	info->s_tiny_map = ft_alloc_align_size((info->s_tiny_request * 
		FT_AN) + (info->s_chunk * FT_AN) + info->s_arena, info->s_page);
	info->s_small_map = ft_alloc_align_size((info->s_small_request *
		FT_AM) + (info->s_chunk * FT_AM) + info->s_arena, info->s_page);
	return (EXIT_SUCCESS);
}

size_t			ft_alloc_align_size(size_t offset, size_t align)
{
	return ((offset % align == 0) ? offset : offset + (align - (offset % align) % align));
}

int				ft_alloc_init(void)
{
	if (g_alloc.info.s_page != 0)
		return (EXIT_SUCCESS);
	if (ft_alloc_init_info() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
