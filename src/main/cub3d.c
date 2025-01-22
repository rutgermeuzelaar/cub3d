/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:13:18 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/22 20:54:54 by rmeuzela      ########   odam.nl         */
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
	ANGLE (Y INVERSE): %f\n" \
	"DIRECTION XY: %f / %f\n \
	FPS: %d\n", \
	game->player.x, \
	game->player.y, \
	inverse_angle_y(game->player.dir_angle), \
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
	cast_ray_all(game->player.rays, &game->player, &game->map, game->minimap, game->screen);
}

void	angle_test(void)
{
	const float	angles[4] = {
		M_PI / 3,
		(2 * M_PI) / 3,
		(4 * M_PI) / 3,
		(5 * M_PI) / 3
	};
	int	i;

	i = 0;
	while (i < 4)
	{
		get_delta_distance(angles[i]);
		i++;
	}
}
int	main(int argc, char **argv)
{
	t_game	game;

	(void)game;
	if (argc != 2 || argv[1] == NULL || check_os_compatibility() == 1)
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
	return (EXIT_SUCCESS);
}
