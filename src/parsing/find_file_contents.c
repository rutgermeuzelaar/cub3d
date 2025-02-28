/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file_contents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:00:38 by nleusden          #+#    #+#             */
/*   Updated: 2025/02/28 13:25:23 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "map.h"
#include "cub3d.h"
#include "utilities.h"
#include "libft.h"

char	*file_check(char *file, char *format)
{
	int		len;
	char	*str2;

	len = ft_strlen(file);
	str2 = NULL;
	if (len < 10 || file == NULL)
		return (NULL);
	str2 = ft_strrchr(file, '.');
	if (str2 == NULL)
		return (NULL);
	if (ft_strncmp(str2, format, 4) == SUCCESS)
		return (file);
	else
		return (NULL);
}

char	*check_folder(const char *a, const char *b)
{
	char	*str;

	str = NULL;
	if (ft_strncmp(a, b, 5) != 0)
		str = ft_strjoin(a, b);
	else
		str = ft_strdup(b);
	if (!str)
		return (NULL);
	return (str);
}

int	find_fd(const char *str, char *folder, char *format)
{
	int		fd;
	char	*folder_copy;

	fd = 0;
	folder = check_folder(folder, str);
	if (!folder)
		return (SYS_ERROR);
	folder_copy = file_check(folder, format);
	if (!folder_copy)
		return (free(folder), SYS_ERROR);
	fd = open(folder_copy, O_RDONLY);
	if (fd < 0)
		return (free(folder), SYS_ERROR);
	return (free(folder), fd);
}

static char	*find_contents(const char *argv)
{
	int		fd;
	char	*str;
	char	*line;

	fd = find_fd(argv, "maps/", ".cub");
	if (fd < 0)
		return (printf("Error FD\n"), NULL);
	str = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			str = ft_strjoin2(str, line);
			if (!str)
				return (printf("Error gnl\n"), free(line), NULL);
			free(line);
		}
		else if (line == NULL)
			break ;
	}
	close(fd);
	if (str == NULL)
		return (printf("Error file empty\n"), NULL);
	return (str);
}

int	get_file_contents(t_game *game_s, const char *str)
{
	char	*str_config;
	char	*str_config_lf;

	str_config = find_contents(str);
	if (!str_config)
		return (ERROR);
	str_config_lf = change_crlf_to_lf(str_config);
	if (!str_config_lf)
		return (printf("Error changing format\n"), free(str_config), SYS_ERROR);
	free(str_config);
	game_s->map.map = ft_split(str_config_lf, '\n');
	if (!game_s->map.map)
		return (printf("Error allocation\n"), free(str_config_lf), SYS_ERROR);
	game_s->file_content = str_config_lf;
	return (SUCCESS);
}
