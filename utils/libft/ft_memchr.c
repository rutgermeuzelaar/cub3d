/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:06:54 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:10:15 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//The memchr() function scans the initial n bytes of the memory
//area pointed to by s for the first instance of c.  Both c and the
//bytes of the memory area pointed to by s are interpreted as
//unsigned char.

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n > 0)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
		n--;
	}
	return (0);
}
