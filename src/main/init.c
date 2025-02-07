/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/01 01:16:22 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/07 20:28:35 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "map.h"
#include "cub3d.h"
#include "minimap.h"
#include "utilities.h"
#include "player.h"

static bool	init_mlx_objects(t_game *const game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!game->mlx)
	{
		return (false);
	}
	game->minimap = mlx_new_image(game->mlx, game->map.width * TILE_SIZE, \
	game->map.height * TILE_SIZE);
	if (!game->minimap)
	{
		mlx_terminate(game->mlx);
		return (false);
	}
	game->screen = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->screen)
	{
		mlx_terminate(game->mlx);
		return (false);
	}
	game->debug = NULL;
	return (printf("finished mlx objects correctly\n"), true);
}

static void	mlx_stop_loop(void *param)
{
	mlx_close_window((mlx_t *)param);
}

static void	mlx_esc(mlx_key_data_t keydata, void *param)
{
	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
	{
		return ;
	}
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_stop_loop(param);
	}
}

static bool	set_mlx_attributes(t_game *game)
{
	if (mlx_image_to_window(game->mlx, game->screen, 0, 0) == -1)
	{
		return (false);
	}
	if (!mlx_loop_hook(game->mlx, draw_routine, game))
	{
		return (false);
	}
	if (!mlx_loop_hook(game->mlx, move_player, game))
	{
		return (false);
	}
	mlx_key_hook(game->mlx, mlx_esc, game->mlx);
	mlx_close_hook(game->mlx, mlx_stop_loop, NULL);
	return (true);
}

bool	init_game(t_game *const game, char *map_name)
{
	if (parsing(game, map_name) != SUCCESS)
	{
		return (false);
	}
	(void)printf("finished parsing\n");
	if (!init_mlx_objects(game))
	{
		free_pointer_array((void **)game->map.map, game->map.height);
		return (false);
	}
	if (!init_player(&game->player, game->map.player_x + 0.5, \
	game->map.player_y + 0.5))
	{
		free_pointer_array((void **)game->map.map, game->map.height);
		mlx_terminate(game->mlx);
		return (false);
	}
	if (!set_mlx_attributes(game))
	{
		free_pointer_array((void **)game->map.map, game->map.height);
		mlx_terminate(game->mlx);
		return (false);
	}
	return (true);
}
