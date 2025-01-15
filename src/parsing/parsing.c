/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 13:35:14 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/14 20:53:40 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utilities.h"

int	get_map(t_game *game)
{
	int	ret;
	char	**arr;
	int	i;
	int	j;

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
			arr_free(game->map.map);
			game->map.map = arr;
			return (SUCCESS);
		}
		i++;
	}
	return (ERROR);
}

int	find_keywords(t_game *game)
{
	int	ret;

	ret = texture_parsing(game);
	if (ret != SUCCESS)
		return (ret);
	ret = fc_parsing(game);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
}

int	parsing(t_game *game, char *arg)
{
	int	ret;

	ret = get_file_contents(game, arg);
	if (ret != SUCCESS)
		return (ret);
	ret = find_keywords(game);
	if (ret != SUCCESS)
		return (ret);
	ret = get_map(game);
	printf("map =\n");
	print_arr(game->map.map);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
}
