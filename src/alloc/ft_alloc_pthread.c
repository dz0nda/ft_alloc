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
	if (g_alloc.mutex == UNINITIALIZED)
	{
		if (pthread_mutex_init(&g_mutex, NULL) != 0)
			return (EXIT_FAILURE);
		g_alloc.mutex = UNLOCKED;
	}
	if (g_alloc.mutex == UNLOCKED)
	{
		if (pthread_mutex_lock(&g_mutex) != 0)
			return (EXIT_FAILURE);
		g_alloc.mutex = LOCKED;
	}
	return (EXIT_SUCCESS);
}

int		ft_alloc_pthread_lock_by_parent(void)
{
	if (g_alloc.mutex == LOCKED)
		g_alloc.mutex = LOCKED_BY_PARENT;
	return (EXIT_SUCCESS);
}

int		ft_alloc_pthread_unlock(void)
{
	if (g_alloc.mutex == LOCKED)
	{
		if (pthread_mutex_unlock(&g_mutex) != 0)
			return (EXIT_FAILURE);
		g_alloc.mutex = UNLOCKED;
	}
	return (EXIT_SUCCESS);
}

int		ft_alloc_pthread_unlock_by_parent(void)
{
	if (g_alloc.mutex == LOCKED_BY_PARENT)
		g_alloc.mutex = LOCKED;
	return (EXIT_SUCCESS);
}
