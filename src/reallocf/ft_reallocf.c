// /* ************************************************************************** */
// /*                                                          LE - /            */
// /*                                                              /             */
// /*   ft_reallocf.c                                    .::    .:/ .      .::   */
// /*                                                 +:+:+   +:    +:  +:+:+    */
// /*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
// /*                                                 #+#   #+    #+    #+#      */
// /*   Created: 2019/09/24 06:16:04 by dzonda       #+#   ##    ##    #+#       */
// /*   Updated: 2019/10/11 21:17:34 by dzonda      ###    #+. /#+    ###.fr     */
// /*                                                         /                  */
// /*                                                        /                   */
// /* ************************************************************************** */

// #include "ft_reallocf.h"

// static void		*ft_reallocf(void *ptr, size_t size)
// {
// 	void	*new;

// 	new = NULL;
// 	ft_alloc_pthread_lock_by_alloc();
// 	new = realloc(ptr, size);
// 	ft_alloc_pthread_unlock_by_alloc();
// 	if (new == NULL)
// 		free(ptr);
// 	return (new);
// }

// void			*reallocf(void *ptr, size_t size)
// {
// 	void	*new;

// 	new = NULL;
// 	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
// 		return (NULL);
// 	new = ft_reallocf(ptr, size);
// 	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
// 		return (NULL);
// 	return (new);
// }
