/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:07:59 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:14:18 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strchr() function returns a pointer to the first occurrence
// of the character c in the string s.

char	*ft_strchr(const char *c, int b)
{
	int	i;

	i = 0;
	if (c[i] == '\0')
	{
		if ((unsigned char)c[i] == (unsigned char)b)
			return (((char *)c) + i);
	}
	while (c[i])
	{
		if ((unsigned char)c[i] == (unsigned char)b)
			return (((char *)c) + i);
		i++;
		if (c[i] == '\0')
		{
			if ((unsigned char)c[i] == (unsigned char)b)
				return (((char *)c) + i);
		}
	}
	return (NULL);
}
