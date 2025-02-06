/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:18:12 by nleusden          #+#    #+#             */
/*   Updated: 2025/02/06 13:53:53 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "color.h"
#include "map.h"
#include "libft.h"
#include "cub3d.h"
#include "utilities.h"

int	*rgb_to_int(char *rgb)
{
	int		*ret;
	char	**arr;
	int		i;

	i = skip_whitespaces(rgb);
	arr = ft_split(rgb + i, ',');
	if (!arr || arrlen(arr) != 3)
		return (NULL);
	ret = ft_calloc(3, sizeof(int));
	if (!ret)
		return (arr_free((void **)arr), NULL);
	while (arr[i])
	{
		ret[i] = ft_atoi(arr[i]);
		if (ret[i] > 255 || ret[i] < 0)
		{
			arr_free((void **)arr);
			return (free(ret), NULL);
		}
		i++;
	}
	ret[i] = '\0';
	arr_free((void **)arr);
	return (ret);
}

int	get_rgb_value(char *rgb, t_color *game)
{
	int		i;
	int		*ret;
	t_color	color;

	i = skip_whitespaces(rgb);
	ret = rgb_to_int(rgb + i);
	if (!ret)
		return (SYS_ERROR);
	color.bytes.alpha = 255;
	color.bytes.red = ret[0];
	color.bytes.green = ret[1];
	color.bytes.blue = ret[2];
	*game = color;
	free(ret);
	return (SUCCESS);
}

int	fc_parsing(t_game *game)
{
	int		i;
	int		j;
	char	**file;
	int		ret;

	i = 0;
	file = game->map.map;
	ret = 0;
	while (file[i])
	{
		j = skip_whitespaces(file[i]);
		if (file[i][j] && file[i][j] == 'F')
			ret = get_rgb_value(file[i] + j + 1, &game->floor);
		else if (file[i][j] && file[i][j] == 'C')
			ret = get_rgb_value(file[i] + j + 1, &game->ceiling);
		if (ret != SUCCESS)
			return (ret);
		i++;
	}
	return (SUCCESS);
}
