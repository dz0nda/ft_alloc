/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/14 06:55:14 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 06:55:24 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_libft.h"

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	unsigned char	set;

	s = (unsigned char *)b;
	set = (unsigned char)c;
	while (len-- > 0)
	{
		*s = set;
		s++;
	}
	return (b);
}
