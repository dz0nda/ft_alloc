/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:37:54 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 06:07:03 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_REALLOC_H
# define FT_REALLOC_H

# include "../malloc/ft_malloc.h"
# include "../free/ft_free.h"

void	*realloc(void *ptr, size_t size);

#endif
