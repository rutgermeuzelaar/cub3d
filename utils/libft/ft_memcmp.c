/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:43:02 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:12:25 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The memcmp() function returns an integer less than, equal to, or
// greater than zero if the first n bytes of s1 is found,
// respectively, to be less than, to match, or be greater than the
// first n bytes of s2.

// For a nonzero return value, the sign is determined by the sign of
// the difference between the first pair of bytes (interpreted as
// unsigned char) that differ in s1 and s2.

// If n is zero, the return value is zero.

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n > i)
	{
		if ((((unsigned char *)s1)[i]) != (((unsigned char *)s2)[i]))
			return ((((unsigned char *)s1)[i]) - (((unsigned char *)s2)[i]));
		i++;
	}
	return (0);
}
