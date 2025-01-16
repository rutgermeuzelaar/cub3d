/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/01 01:16:22 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/16 17:11:34 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "minimap.h"
#include "utilities.h"
#include "player.h"

bool	init_map(t_map *const map)
{
	size_t		i;
	const char	*cheese[] = {
		"111111",
		"100101",
		"101001",
		"1100N1",
		"111111"
	};
	i = 0;
	map->height = 5;
	map->width = 6;
	map->map = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->map)
	{
		return (false);
	}
	while (i < map->height)
	{
		map->map[i] = ft_strdup(cheese[i]);
		if (!map->map[i])
		{
			free_pointer_array((void **)map->map, i);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_mlx_objects(t_game *const game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!game->mlx)
	{
		return false;
	}
	game->minimap = mlx_new_image(game->mlx, game->map.width * TILE_SIZE, \
	game->map.height * TILE_SIZE);
	if (!game->minimap)
	{
		mlx_terminate(game->mlx);
		return false;
	}
	game->screen = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->screen)
	{
		mlx_terminate(game->mlx);
		return false;
	}
	game->debug = NULL;
	return (printf("finished mlx objects correctly\n"), true);
}

bool	init_game(t_game *const game)
{
	if (!init_mlx_objects(game))
	{
		free_pointer_array((void **)game->map.map, game->map.height);
		return (false);
	}
	init_player(&game->player, game->map.player_x * TILE_SIZE + (TILE_SIZE / 2), \
	game->map.player_y * TILE_SIZE + (TILE_SIZE / 2));
	return (true);
}
