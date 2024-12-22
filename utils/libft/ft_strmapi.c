/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:54:12 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:18:10 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Applies the function ’f’ to each character of the
// string ’s’, and passing its index as first argument
// to create a new string (with malloc(3)) resulting
// from successive applications of ’f’.

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*allocate;

	i = 0;
	len = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[len])
		len++;
	allocate = (char *)malloc((len + 1) * sizeof(char));
	if (allocate == NULL)
		return (NULL);
	while (s[i] && len > i)
	{
		allocate[i] = f(i, s[i]);
		i++;
	}
	allocate[len] = '\0';
	return (allocate);
}
