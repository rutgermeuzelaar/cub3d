/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:53:56 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:26:32 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strlen() function calculates the length of the string pointed
// to by s, excluding the terminating null byte ('\0').

size_t	ft_strlen(const char *x)
{
	size_t	y;

	y = 0;
	while (x[y])
	{
		y++;
	}
	return (y);
}
