/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nilsleusden@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:13:18 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/17 15:03:52 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "cub3d.h"
#include "MLX42/MLX42.h"
#include "map.h"
#include "minimap.h"
#include "libft.h"
#include "shapes.h"
#include "player.h"
#include "raycasting.h"

// int	main(int argc, char **argv)
// {
// 	t_game	*game_struct;

// 	if (argc != 2 && argv[1] == NULL)
// 		return (ERROR);
// 	game_struct = ft_calloc(2, sizeof(t_game));
// 	if (!game_struct)
// 		return (ERROR);
// 	if (check_file(argv[1], game_struct) == SUCCESS)
// 	{
// 		print_arr(game_struct->map);
// 		return (SUCCESS);
// 	}
// 	return (ERROR);
// }

void	mlx_stop_loop(void *param)
{
	mlx_close_window((mlx_t *)param);
}

void	mlx_esc(mlx_key_data_t keydata, void *param)
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

// Only for debugging, remove in final project.
void	draw_info(t_game *game)
{
	char		player[1000];
	mlx_image_t	*old_img;

	sprintf(player, \
	"PLAYER XY: %f / %f\n \
	ANGLE: %f\n" \
	"DIRECTION XY: %f / %f\n \
	FPS: %d\n", \
	game->player.x, \
	game->player.y, \
	game->player.dir_angle, \
	game->player.dir.x, \
	game->player.dir.y,
	(int)(1 / game->mlx->delta_time));
	old_img = game->debug;
	game->debug = mlx_put_string(game->mlx, player, 16, 16);
	mlx_delete_image(game->mlx, old_img);
}

void	draw_routine(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_info(game);
	draw_rectangle(game->screen, \
	(t_rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, get_rgba(0x008080, 235));
	ft_memset(game->minimap->pixels, 255, 
	game->minimap->width * game->minimap->height * BPP);
	draw_minimap(&game->map, game->minimap);
	draw_player(&game->player, game->minimap);
	cast_ray(&game->player.ray, &game->player, &game->map, game->minimap);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || argv[1] == NULL)
		return (ERROR);
	if (parsing(&game, argv[1]) != SUCCESS)
	{
		return (ERROR);
	}
	printf("finished parsing\n");
	if (!init_game(&game))
	{
		return (EXIT_FAILURE);
	}
	draw_rectangle(game.screen, \
	(t_rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, get_rgba(0x008080, 235));
	mlx_image_to_window(game.mlx, game.screen, 0, 0);
	mlx_image_to_window(game.mlx, game.minimap, 100, 300);
	mlx_loop_hook(game.mlx, move_player, &game);
	mlx_loop_hook(game.mlx, draw_routine, &game);
	mlx_key_hook(game.mlx, mlx_esc, game.mlx);
	mlx_close_hook(game.mlx, mlx_stop_loop, NULL);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
