/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:18:15 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:22:49 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//if c is lowercase itll change to uppercase

int	ft_toupper(int c)
{
	int	x;

	x = 32;
	if (c <= 122 && c >= 97)
	{
		c -= x;
	}
	return (c);
}
