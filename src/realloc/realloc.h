/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:37:54 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 07:37:55 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_REALLOC_H
# define FT_REALLOC_H

# include "../malloc/malloc.h"
# include "../free/free.h"

void	*ft_realloc(void *ptr, size_t size);

#endif