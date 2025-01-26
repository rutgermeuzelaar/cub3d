/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:13:18 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/26 21:13:07 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
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

float	inverse_angle_y(float angle)
{
	const float	half = M_PI * 2;

	return ((angle - half) * -1);
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
	game->player.dir_x, \
	game->player.dir_y,
	(int)(1 / game->mlx->delta_time));
	old_img = game->debug;
	game->debug = mlx_put_string(game->mlx, player, 16, 16);
	mlx_delete_image(game->mlx, old_img);
}

static void draw_background(mlx_image_t *screen, t_color floor, t_color ceiling)
{
	const int 	half_window_height = WINDOW_HEIGHT / 2;

	draw_rectangle(screen, \
	(t_rectangle){0, 0, WINDOW_WIDTH, half_window_height}, ceiling.rgba);
	draw_rectangle(screen, \
	(t_rectangle){0, half_window_height, WINDOW_WIDTH, half_window_height}, floor.rgba);
}

void	draw_movement_cross(float angle, t_vector2d position, \
		mlx_image_t *minimap)
{
	const float quarter = RADIAN * 45;
	const float	radius = 0.4;
	t_vector2d	circle_point_1;
	t_vector2d	circle_point_2;
	int	i;

	i = 0;
	while (i < 4)
	{
		circle_point_1 = position;
		circle_point_2 = position;
		circle_point_1.x += cos(angle + quarter * (i + 1)) * radius;
		circle_point_1.y += sin(angle + quarter * (i + 1)) * radius;
		circle_point_2.x += position.x - circle_point_1.x;
		circle_point_2.y += position.y - circle_point_1.y;
		draw_line((t_vector2dint){circle_point_1.x * TILE_SIZE, circle_point_1.y * TILE_SIZE}, \
		(t_vector2dint){circle_point_2.x * TILE_SIZE, circle_point_2.y *TILE_SIZE},minimap, RED);
		i++;
	}
}

void	draw_routine(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_info(game);
	draw_background(game->screen, game->floor, game->ceiling);
	ft_memset(game->minimap->pixels, 255, 
	game->minimap->width * game->minimap->height * BPP);
	draw_minimap(&game->map, game->minimap);

	draw_player(&game->player, game->minimap);

	draw_movement_cross(game->player.dir_angle, (t_vector2d){game->player.x, game->player.y}, game->minimap);
	cast_ray_all(game->player.rays, &game->player, &game->map, game->minimap, game->screen);
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)game;
	if (argc != 2 || argv[1] == NULL || check_os_compatibility() == 1)
		return (ERROR);
	if (parsing(&game, argv[1]) != SUCCESS)
		return (ERROR);
	printf("finished parsing\n");
	if (!init_game(&game))
	{
		return (EXIT_FAILURE);
	}
	// angle_test();
	draw_rectangle(game.screen, 
	(t_rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, get_rgba(0x008080, 235));
	mlx_image_to_window(game.mlx, game.screen, 0, 0);
	mlx_image_to_window(game.mlx, game.minimap, 900, WINDOW_HEIGHT / 8);
	mlx_loop_hook(game.mlx, move_player, &game);
	mlx_loop_hook(game.mlx, draw_routine, &game);
	mlx_key_hook(game.mlx, mlx_esc, game.mlx);
	mlx_close_hook(game.mlx, mlx_stop_loop, NULL);
	mlx_loop(game.mlx);
	free_function(&game);
	return (EXIT_SUCCESS);
}
