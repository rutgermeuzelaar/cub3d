/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:31:26 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:14:42 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strrchr() function returns a pointer to the last occurrence
// of the character c in the string s.

char	*ft_strrchr(const char *c, int b)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	while (i >= 0)
	{
		if ((unsigned char)c[i] == (unsigned char)b)
			return ((char *)(c + i));
		i--;
	}
	return (0);
}
