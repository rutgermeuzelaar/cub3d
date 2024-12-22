/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:54:42 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:22:32 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//if int c is uppercase itll change c to lowercase

int	ft_tolower(int c)
{
	int	x;

	x = 32;
	if (c <= 90 && c >= 65)
	{
		c += x;
	}
	return (c);
}
