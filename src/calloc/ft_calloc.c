/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_calloc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:42:48 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 06:20:15 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_calloc.h"

static void *ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = NULL;
	size *= count;
	ft_alloc_pthread_lock_by_parent();
	new = malloc(size);
	ft_alloc_pthread_unlock_by_parent();
	if (new == NULL)
		return (NULL);
	ft_alloc_memset(new, 0, size);
}

void		*calloc(size_t count, size_t size)
{
	void	*new;

	new = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return (NULL);
	new = ft_calloc(count, size);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return (NULL);
	return (new);
}
