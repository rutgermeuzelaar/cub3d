/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nilsleusden@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:13:18 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/06 20:23:27 by rmeuzela      ########   odam.nl         */
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
	int		i;
	int		map_x;
	int		map_y;
	float	ray_x_offset;
	float	ray_y_offset;
	float	a_tan;

	i = 0;
	a_tan = -1/tan(player->dir_angle);
	printf("a_tan: %f\n", a_tan);
	ray->position.x = player->rectangle.x;
	ray->position.y = player->rectangle.y;
	// horizontal
	// looking up
	if (player->dir_angle < M_PI)
	{
		ray->direction.y = (((int)player->rectangle.y>>6)<<6)-0.0001;
		ray->direction.x = ((player->rectangle.y - ray->direction.y) * a_tan) + player->rectangle.x;
		ray_y_offset = -TILE_SIZE;
		ray_x_offset = -ray_y_offset * a_tan;
	}
	// looking down
	while (i < 4)
	{
		map_x = (int)ray->direction.x>>6;
		map_y = (int)ray->direction.y>>6;
		if ((size_t)map_x > map->width - 1 || map_x < 0)
		{
			break ;
		}
		if ((size_t)map_y > map->height -1 || map_y < 0)
		{
			break ;
		}
		if (map->map[map_y][map_x] == '1')
		{
			break ;
		}
		ray->direction.x += ray_x_offset;
		ray->direction.y += ray_y_offset; 
		i++;
	}
	if (ray->direction.x < 0)
	{
		ray->direction.x = 0;
	}
	if (ray->direction.y < 0)
	{
		ray->direction.y = 0;
	}
	draw_line(player->rectangle.x + (player->rectangle.width / 2), \
	player->rectangle.y + (player->rectangle.height / 2), ray->direction.x, ray->direction.y, \
	minimap, get_rgba(0x00ff00,255));
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
	game->player.rectangle.x, \
	game->player.rectangle.y, \
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
	// draw_ray(&game->player, &game->map, game->minimap, &game->player.ray);
	draw_info(game);
	draw_rectangle(game->screen, \
	(t_rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, get_rgba(0x008080, 235));
	ft_memset(game->minimap->pixels, 255, 
	game->minimap->width * game->minimap->height * BPP);
	draw_minimap(&game->map, game->minimap);
	draw_player(&game->player, game->minimap);
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
