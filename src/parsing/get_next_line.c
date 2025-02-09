/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 13:33:14 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/31 18:46:47 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "cub3d.h"
#include "utilities.h"

char	*reading_f(int fd, char *tempstr)
{
	char	*buffer;
	int		bytesread;

	bytesread = BUFFER_SIZE;
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(buffer, '\n') && bytesread == BUFFER_SIZE)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (free(buffer), free(tempstr), NULL);
		if (bytesread == 0)
			break ;
		buffer[bytesread] = '\0';
		tempstr = ft_strjoin2(tempstr, buffer);
		if (!tempstr)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (tempstr);
}

char	*newlinecut(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		i++;
	}
	if (str[i] == '\n')
		i++;
	line = (char *)ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i])
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*skipfunction(char *tempstr)
{
	char	*tempstr2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!tempstr)
		return (NULL);
	while (tempstr[i] && tempstr[i] != '\n')
		i++;
	if (tempstr[i] != '\n' || tempstr[i] == '\0')
		return (free(tempstr), NULL);
	tempstr2 = (char *)ft_calloc(sizeof(char), (ft_strlen(tempstr) - i + 1));
	if (!tempstr2)
		return (NULL);
	i++;
	while (tempstr[i])
		tempstr2[j++] = tempstr[i++];
	tempstr2[j] = '\0';
	free(tempstr);
	return (tempstr2);
}

char	*get_next_line(int fd)
{
	static char	*tempstr[1024];
	char		*line;

	if (fd < 0 || !BUFFER_SIZE)
		return (NULL);
	tempstr[fd] = reading_f(fd, tempstr[fd]);
	if (!tempstr[fd])
		return (NULL);
	line = newlinecut(tempstr[fd]);
	tempstr[fd] = skipfunction(tempstr[fd]);
	return (line);
}
