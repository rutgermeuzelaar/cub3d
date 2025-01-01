/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nilsleusden@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 13:35:14 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/01 20:59:21 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utilities.h"

char	*file_check(char *file)
{
	int		len;
	char	*str;
	char	*str2;

	len = ft_strlen(file);
	str = ".cub";
	str2 = NULL;
	if (len < 10 || file == NULL)
		return (free(file), NULL);
	str2 = ft_strrchr(file, '.');
	if (str2 == NULL)
		return (free(file), NULL);
	if (ft_strncmp(str2, str, 4) == SUCCESS)
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

int	find_fd(char *str)
{
	char	*str2;
	int		fd;

	fd = 0;
	str2 = "maps/";
	str2 = check_folder(str2, str);
	if (!str)
		return (SYS_ERROR);
	printf("str2 = %s\n", str2);
	str2 = file_check(str2);
	fd = open(str2, O_RDONLY);
	if (fd < 0)
		return (free(str2), printf("error FD\n"), SYS_ERROR);
	return (fd);
}

char	*find_map(char *argv)
{
	int		fd;
	char	*str;
	char	*line;

	fd = find_fd(argv);
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

int	check_file(char *str, t_game *game_s)
{
	char	**map;
	char	*str_map;

	str_map = find_map(str);
	if (!str_map)
		return (ERROR);
	map = ft_split(str_map, '\n');
	if (!map)
		return (SYS_ERROR);
	game_s->map.map = map;
	return (SUCCESS);
}
