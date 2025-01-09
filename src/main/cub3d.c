/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nilsleusden@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:13:18 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/08 21:16:32 by rmeuzela      ########   odam.nl         */
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

void	draw_ray(t_player *player, t_map *map, mlx_image_t *minimap, t_ray *ray)
{
	int				i;
	t_vector2dint	map_point;
	float			ray_x_offset;
	float			ray_y_offset;
	float			a_tan;

	i = 0;
	a_tan = -1/tan(player->dir_angle);
	printf("a_tan: %f\n", a_tan);
	ray->position.x = player->x;
	ray->position.y = player->y;
	// horizontal
	// looking up
	(void)map;
	(void)minimap;
	if (player->dir_angle > M_PI)
	{
		ray->direction.y = (((int)player->y>>6)<<6)-0.0001;
		ray->direction.x = (ray->position.y - ray->direction.y) * a_tan + ray->position.x;
		ray_y_offset = -TILE_SIZE;
		ray_x_offset = -ray_y_offset * a_tan;
	}
	printf("ray->direction.y: %f ray->direction.x: %f ray_y_offset: %f ray_x_offset: %f\n\n", ray->direction.y, ray->direction.x, ray_y_offset, \
	ray_x_offset);
	if (player->dir_angle == 0 || player->dir_angle == M_PI)
	{
		ray->direction.y = player->y;
		ray->direction.x = player->x;
		i = 5;
	}
	while (i < 6)
	{
		map_point.x = ray->direction.y / TILE_SIZE;
		map_point.y = ray->direction.x / TILE_SIZE;
		printf("map_point.x: %d map_point.y: %d\n", map_point.x, map_point.y);
		if ((size_t)map_point.x > map->width - 1 || (size_t)map_point.y > map->height - 1)
		{
			break ;
		}
		if (map_point.x < 0 || map_point.y < 0)
		{
			break;
		}
		if (map->map[map_point.y][map_point.x] == '1')
		{
			break ;
		}
		ray->direction.y += ray_y_offset;
		ray->direction.x += ray_x_offset;
		i++;
	}
	draw_line(ray->position.x, ray->position.y, ray->direction.x, \
	ray->direction.y, minimap, get_rgba(0x00ff00, 255));
	// looking down
}

// Only for debugging, remove in final project.
void	draw_info(t_game *game)
{
	char		player[100];
	mlx_image_t	*old_img;

	sprintf(player, \
	"PLAYER XY: %f / %f\n \
	ANGLE: %f\n" \
	"DIRECTION XY: %f / %f\n", \
	game->player.x, \
	game->player.y, \
	game->player.dir_angle, \
	game->player.dir.x, \
	game->player.dir.y);
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
	draw_ray(&game->player, &game->map, game->minimap, &game->player.ray);
}

int	main(void)
{
	t_game	game;

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
