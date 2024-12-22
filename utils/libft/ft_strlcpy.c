/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:00:34 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:25:58 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//The strlcpy() function copies up to size - 1 characters
//from the NUL-terminated string src to dst, NUL-terminating the result.

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srcl;

	i = 0;
	srcl = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i + 1 < size)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[srcl])
	{
		srcl++;
	}
	return (srcl);
}
