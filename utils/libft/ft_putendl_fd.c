/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:30:18 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:23:54 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Outputs the string ’s’ to the given file descriptor
//followed by a newline.

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	endl;

	i = 0;
	endl = '\n';
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	if (s[i] == '\0')
		write(fd, &endl, 1);
}
