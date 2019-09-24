/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_reallocf.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/24 06:16:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 06:23:51 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_reallocf.h"

void		*reallocf(void *ptr, size_t size)
{
	void	*new;

	new = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return (NULL);
	ft_alloc_pthread_lock_by_parent();
	new = realloc(ptr, size);
	ft_alloc_pthread_unlock_by_parent();
	if (new == NULL)
		free(ptr);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return (NULL);
	return (new);
}
