/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:00:02 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:19:57 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strncmp() function shall compare not more than n bytes (bytes
// that follow a NUL character are not compared) from the array
// pointed to by s1 to the array pointed to by s2.

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && n > 0)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}
		if (s1[i] != s2[i])
		{
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		}
		i++;
		n--;
	}
	return (0);
}
