/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc_pthread.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/24 06:14:55 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 06:19:58 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_alloc.h"

int		ft_alloc_pthread_lock(void)
{
	if (g_alloc.mutex == FT_UNINITIALIZED)
	{
		if (pthread_mutex_init(&g_mutex, NULL) != 0)
			return (EXIT_FAILURE);
		g_alloc.mutex = FT_UNLOCKED;
	}
	if (g_alloc.mutex == FT_UNLOCKED)
	{
		if (pthread_mutex_lock(&g_mutex) != 0)
			return (EXIT_FAILURE);
		g_alloc.mutex = FT_LOCKED;
	}
	return (EXIT_SUCCESS);
}

int		ft_alloc_pthread_lock_by_alloc(void)
{
	if (g_alloc.mutex == FT_LOCKED)
		g_alloc.mutex = FT_LOCKED_BY_ALLOC;
	return (EXIT_SUCCESS);
}

int		ft_alloc_pthread_unlock(void)
{
	if (g_alloc.mutex == FT_LOCKED)
	{
		if (pthread_mutex_unlock(&g_mutex) != 0)
			return (EXIT_FAILURE);
		g_alloc.mutex = FT_UNLOCKED;
	}
	return (EXIT_SUCCESS);
}

int		ft_alloc_pthread_unlock_by_alloc(void)
{
	if (g_alloc.mutex == FT_LOCKED_BY_ALLOC)
		g_alloc.mutex = FT_LOCKED;
	return (EXIT_SUCCESS);
}
