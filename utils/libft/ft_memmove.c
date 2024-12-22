/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:40:58 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:13:04 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The memmove() function copies n bytes from memory area src to
// memory area dest.  The memory areas may overlap: copying takes
// place as though the bytes in src are first copied into a
// temporary array that does not overlap src or dest, and the bytes
// are then copied from the temporary array to dest.

void	*overlapcheck(unsigned char	*p1, const unsigned char *p2, size_t n)
{
	int	i;

	i = n - 1;
	while (i >= 0)
	{
		p1[i] = p2[i];
		i--;
	}
	return (p1);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p1;
	const unsigned char	*p2;

	p1 = dest;
	p2 = src;
	if (p1 == p2)
		return (p1);
	if (p1 < p2)
	{
		while (n > 0)
		{
			*p1 = *p2;
			p1++;
			p2++;
			n--;
		}
	}
	else
		overlapcheck(p1, p2, n);
	return ((unsigned char *)dest);
}
