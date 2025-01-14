/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:28:51 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/14 13:53:18 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	map_dimensions(t_game *game)
{
	int		i;
	size_t	maxlen;
	int	ppos[2];

	i = 0;
	maxlen = 0;
	ppos[0] = 0;
	ppos[1] = 0;
	while (game->map.map[i])
	{
		if (ft_strlen(game->map.map[i]) > maxlen)
			maxlen = ft_strlen(game->map.map[i]);
		if (find_pos(game->map.map[i]) > 0)
			ppos[1] = find_pos(game->map.map[i]);
		if (ppos[1] > 0)
			ppos[0] = i;
		i++;
	}
	printf("player position =\nx = %d\ny = %d\n", ppos[1], ppos[0]);
	printf("width = %zu\nheight = %d\n", maxlen, i);
	game->map.height = i;
	game->map.width = maxlen;
	game->map.player_y = ppos[0];
	game->map.player_x = ppos[1];
	return (SUCCESS);
}


int	get_map(t_game *game)
{
	int	ret;
	char	**arr;
	int	i;
	int	j;

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
			arr_free(game->map.map);
			game->map.map = arr;
			return (SUCCESS);
		}
		i++;
	}
	return (ERROR);
}
