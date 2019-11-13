/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_calloc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:42:48 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 21:13:19 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_calloc.h"

static void		*ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = NULL;
	size *= count;
	if (pthread_mutex_unlock(&g_mutex) != 0)
		return (NULL);
	new = malloc(size);
	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	if (new == NULL)
		return (NULL);
	ft_memset(new, 0, size);
	return (new);
}

void			*calloc(size_t count, size_t size)
{
	void	*new;

	new = NULL;
	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	if (ft_alloc_init() == EXIT_SUCCESS)
		new = ft_calloc(count, size);
	if (pthread_mutex_unlock(&g_mutex) != 0)
		return (NULL);
	return (new);
}
