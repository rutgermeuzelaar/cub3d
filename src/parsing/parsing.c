/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:35:14 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/14 15:35:38 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utilities.h"

int	pre_parsing(char *str)
{
	int	ret;

	ret = find_all_prefix(str);
	if (ret != SUCCESS)
		return (ret);
	// ret = check_map_format(str);
	// if (ret != SUCCESS)
	// 	return (ret);
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
	// ret = pre_parsing(game->file_content);
	// if (ret != SUCCESS)
	// 	return (ERROR);
	ret = find_keywords(game);
	if (ret != SUCCESS)
		return (ret);
	ret = get_map(game);
	if (ret != SUCCESS)
		return (ret);
	printf("map =\n");
	print_arr(game->map.map);
	ret = map_dimensions(game);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
}
