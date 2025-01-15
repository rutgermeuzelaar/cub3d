/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:35:14 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/15 16:23:50 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utilities.h"

int	check_map_format(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (0);
}

int	pre_parsing(char *str)
{
	int	ret;
	int	i;

	i = 0;
	ret = find_all_prefix(str, &i);
	if (ret != SUCCESS)
		return (ret);
	ret = check_map_format(str + i);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
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
	ret = pre_parsing(game->file_content);
	if (ret != SUCCESS)
		return (ERROR);
	ret = find_keywords(game);
	if (ret != SUCCESS)
		return (ret);
	ret = get_map(game);
	if (ret != SUCCESS)
		return (ret);
	ret = map_dimensions(game);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
}
