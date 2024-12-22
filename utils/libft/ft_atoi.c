/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:39:41 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:02:42 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//The atoi() function converts the initial portion of the string
//pointed to by nptr to int.

int	ft_atoi(const char *nptr)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 1;
	x = 0;
	while ((nptr[i] <= 13 && nptr[i] >= 9) || nptr[i] == 32)
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			j = -1;
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		x = x * 10 + (nptr[i] - '0');
		i++;
	}
	return (j * x);
}
