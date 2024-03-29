/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:11:30 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 06:55:40 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*srce;
	unsigned char		*dest;

	srce = src;
	dest = dst;
	if (srce <= dest)
	{
		srce += len - 1;
		dest += len - 1;
		while (len--)
			*dest-- = *srce--;
	}
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}
