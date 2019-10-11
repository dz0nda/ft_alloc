/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_show_info.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 21:20:57 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 21:22:06 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_show.h"

void			show_alloc_info(void)
{
	t_ainfo		info;

	ft_alloc_memcpy(&info, &(g_alloc).info, sizeof(t_ainfo));
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return ;
	ft_putstr("|| show_alloc_info ||\n\n");
	ft_show_alloc_detail("Soft limit max allocated bytes", info.rlim_cur, FT_TRUE, -1);
	ft_show_alloc_detail("Hard limit max allocated bytes", info.rlim_max, FT_TRUE, -1);
	ft_show_alloc_detail("Size of chunk", info.size_chunk, FT_TRUE, -1);
	ft_show_alloc_detail("Size of arena", info.size_arena, FT_TRUE, -1);
	ft_show_alloc_detail("Pagesize", info.pagesize, FT_TRUE, -1);
	ft_show_alloc_detail("Tiny size request", info.tiny_size_request, FT_TRUE, -1);
	ft_show_alloc_detail("Small size request", info.small_size_request, FT_TRUE, -1);
	ft_show_alloc_detail("Tiny size arena", info.tiny_size_map, FT_TRUE, -1);
	ft_show_alloc_detail("Small size arena", info.small_size_map, FT_TRUE, -1);
	ft_putstr("\n");
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return ;
}

