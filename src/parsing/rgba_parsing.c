/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:18:12 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/16 13:41:32 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utilities.h"

int	*rgb_to_int(char *rgb)
{
	int		*ret;
	char	**arr;
	int		i;

	i = skip_whitespaces(rgb + 1);
	arr = ft_split(rgb + i, ',');
	if (!arr || arrlen(arr) != 3)
		return (NULL);
	ret = ft_calloc(3, sizeof(int));
	if (!ret)
		return (arr_free(arr), NULL);
	while (arr[i])
	{
		ret[i] = ft_atoi(arr[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	get_rgb_value(char *rgb, t_color *game)
{
	int		i;
	int		*ret;
	t_color	color;

	i = (skip_whitespaces(rgb + 1) + 1);
	printf("rgb = %s\n", rgb + i);
	ret = rgb_to_int(rgb);
	if (!ret)
		return (SYS_ERROR);
	color.s_bytes.alpha = 255;
	color.s_bytes.red = ret[0];
	color.s_bytes.green = ret[1];
	color.s_bytes.blue = ret[2];
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
