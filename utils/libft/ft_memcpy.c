/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:06:47 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:11:29 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//The memcpy() function copies n bytes from memory area src to
//memory area dest.  The memory areas must not overlap.  Use
//memmove(3) if the memory areas do overlap.

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*q;

	p = dest;
	q = src;
	if (!dest && !src)
		return (NULL);
	while (n > 0)
	{
		*p = *q;
		p++;
		q++;
		n--;
	}
	return (dest);
}
