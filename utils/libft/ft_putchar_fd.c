/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:50:53 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:23:36 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Outputs the character ’c’ to the given file
//descriptor.

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
