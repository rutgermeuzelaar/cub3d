/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:44:54 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:15:10 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strdup() function returns a pointer to a new string which is
// a duplicate of the string s.  Memory for the new string is
// obtained with malloc(3), and can be freed with free(3).

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dst;

	i = 0;
	dst = malloc (ft_strlen(s) + 1);
	if (dst == NULL)
		return (0);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
