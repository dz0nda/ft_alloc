/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_reallocf.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/24 06:16:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 21:17:34 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_reallocf.h"

static void		*ft_reallocf(void *ptr, size_t size)
{
	void	*new;

	new = NULL;
	if (pthread_mutex_unlock(&g_mutex) != 0)
		return (NULL);
	new = realloc(ptr, size);
	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	if (new == NULL)
		free(ptr);
	return (new);
}

void			*reallocf(void *ptr, size_t size)
{
	void	*new;

	new = NULL;
	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	if (ft_alloc_init() == EXIT_SUCCESS)
		new = ft_reallocf(ptr, size);
	if (pthread_mutex_unlock(&g_mutex) != 0)
		return (NULL);
	return (new);
}
