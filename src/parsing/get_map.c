/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/14 13:28:51 by nleusden      #+#    #+#                 */
/*   Updated: 2025/02/07 20:44:39 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "map.h"
#include "libft.h"
#include "cub3d.h"
#include "utilities.h"

int	find_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			return (i);
		i++;
	}
	return (-1);
}

static void	set_player_direction(t_map *map, const char symbol)
{
	t_cardinal_direction	cardinal;

	cardinal = CARDINAL_NONE;
	if (symbol == 'N')
	{
		cardinal = NORTH;
	}
	if (symbol == 'E')
	{
		cardinal = EAST;
	}
	if (symbol == 'S')
	{
		cardinal = SOUTH;
	}
	if (symbol == 'W')
	{
		cardinal = WEST;
	}
	map->cardinal = cardinal;
}

int	map_dimensions(t_game *game)
{
	int		i;
	size_t	maxlen;
	int		ppos[2];

	i = 0;
	maxlen = 0;
	ppos[0] = 0;
	ppos[1] = 0;
	while (game->map.map[i])
	{
		if (ft_strlen(game->map.map[i]) > maxlen)
			maxlen = ft_strlen(game->map.map[i]);
		if (find_pos(game->map.map[i]) > 0)
		{
			ppos[1] = find_pos(game->map.map[i]);
			ppos[0] = i;
			set_player_direction(&game->map, game->map.map[i][ppos[1]]);
		}
		i++;
	}
	game->map.height = i;
	game->map.width = maxlen;
	game->map.player_y = ppos[0];
	game->map.player_x = ppos[1];
	return (SUCCESS);
}

int	get_map(t_game *game)
{
	int		ret;
	char	**arr;
	int		i;
	int		j;

	(void)ret;
	ret = 0;
	arr = game->map.map;
	i = 0;
	j = 0;
	while (arr[i])
	{
		j = skip_whitespaces(arr[i]);
		if (arr[i][j] && ft_isdigit(arr[i][j]))
		{
			arr = ft_arrndup(arr + i, (arrlen(arr) - i));
			if (!arr)
				return (SYS_ERROR);
			arr_free((void **)game->map.map);
			game->map.map = arr;
			return (SUCCESS);
		}
		i++;
	}
	return (ERROR);
}
