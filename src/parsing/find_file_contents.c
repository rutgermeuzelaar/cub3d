/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file_contents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:00:38 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/16 13:42:47 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utilities.h"

char	*file_check(char *file, char *format)
{
	int		len;
	char	*str2;

	len = ft_strlen(file);
	str2 = NULL;
	if (len < 10 || file == NULL)
		return (free(file), NULL);
	str2 = ft_strrchr(file, '.');
	if (str2 == NULL)
		return (free(file), NULL);
	if (ft_strncmp(str2, format, 4) == SUCCESS)
		return (file);
	else
		return (free(file), NULL);
}

char	*check_folder(char *a, char *b)
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

int	find_fd(char *str, char *folder, char *format)
{
	int	fd;

	fd = 0;
	folder = check_folder(folder, str);
	if (!str)
		return (SYS_ERROR);
	printf("arg found = %s\n", folder);
	folder = file_check(folder, format);
	fd = open(folder, O_RDONLY);
	if (fd < 0)
		return (free(folder), printf("error FD\n"), SYS_ERROR);
	return (fd);
}

char	*find_contents(char *argv)
{
	int		fd;
	char	*str;
	char	*line;

	fd = find_fd(argv, "maps/", ".cub");
	str = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			str = ft_strjoin2(str, line);
			free(line);
		}
		else if (line == NULL)
			break ;
	}
	close(fd);
	return (str);
}

int	get_file_contents(t_game *game_s, char *str)
{
	char	**map;
	char	*str_config;

	str_config = find_contents(str);
	if (!str_config)
		return (ERROR);
	map = ft_split(str_config, '\n');
	if (!map)
		return (SYS_ERROR);
	game_s->file_content = str_config;
	game_s->map.map = map;
	return (SUCCESS);
}
