/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nilsleusden@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 13:35:14 by nleusden      #+#    #+#                 */
/*   Updated: 2025/02/13 16:23:45 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "utilities.h"
#include "minimap.h"

static int	pre_parsing(const char *str)
{
	int	ret;
	int	i;

	i = 0;
	ret = find_all_prefix(str, &i);
	if (ret != SUCCESS)
		return (ret);
	ret = check_map_format(str, i);
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

int	parsing(t_game *game, const char *arg)
{
	int	ret;

	ret = get_file_contents(game, arg);
	if (ret != SUCCESS)
		return (ret);
	ret = pre_parsing(game->file_content);
	if (ret != SUCCESS)
		return (pre_parsing_free(game), ERROR);
	ret = find_keywords(game);
	if (ret != SUCCESS)
		return (parsing_free(game), ret);
	ret = get_map(game);
	if (ret != SUCCESS)
		return (parsing_free(game), ret);
	ret = map_dimensions(game);
	if (ret != SUCCESS)
		return (parsing_free(game), ret);
	if (!pad_map(&game->map))
		return (parsing_free(game), ERROR);
	free(game->file_content);
	return (SUCCESS);
}
