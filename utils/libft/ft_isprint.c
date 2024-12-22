/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:38:20 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:08:46 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//checks if c is a printable character

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (2048);
	}
	else
		return (0);
}
