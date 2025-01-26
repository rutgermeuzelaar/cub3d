/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 15:06:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/26 16:20:00 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <stdio.h>
#include <math.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "cub3d.h"
#include "raycasting.h"

#include "minimap.h"

void	move_angle_right(t_player *player)
{
	player->dir_angle += ROTATION_SPEED;
	if (player->dir_angle >= (2 * M_PI))
	{
		player->dir_angle -= 2 * M_PI;
	}
	player->dir_x = cos(player->dir_angle);
	player->dir_y = sin(player->dir_angle);
}

void	move_angle_left(t_player *player)
{
	player->dir_angle -= ROTATION_SPEED;
	if (player->dir_angle <= 0)
	{
		player->dir_angle += 2 * M_PI;
	}
	player->dir_x = cos(player->dir_angle);
	player->dir_y = sin(player->dir_angle);
}

void	normalize_vector(float *x, float *y)
{
	const float magnitude = sqrt(pow(*y, 2) + pow(*x, 2));
	const float	old_x = *x;
	const float old_y = *y;

	*x *= (*x / magnitude);
	*y *= (*y / magnitude);
	if (old_x < 0)
	{
		*x *= -1;
	}
	if (old_y < 0)
	{
		*y *= -1;
	}
	return ;
}

bool	collide_circle(t_vector2d position, t_map *map, const float radius, \
		mlx_image_t *minimap)
{
	float		i;
	t_vector2d	circle_point;
	t_vector2dint	circle_line;
	t_vector2dint	map_intersection;
	float			a_y;
	float			a_x;
	i = 0;
	circle_point.x = 0;
	circle_point.y = 0;
	(void)map;
	while (i < (M_PI * 2))
	{
		circle_point.x = cos(i) * radius;
		circle_point.y = sin(i) * radius;
		a_y = position.y + circle_point.y;
		a_x = position.x + circle_point.x;
		map_intersection.x = (int)a_x;
		map_intersection.y = (int)a_y;
		circle_line.x = (position.x + circle_point.x) * TILE_SIZE;
		circle_line.y = (position.y + circle_point.y) * TILE_SIZE;
		if (map->map[map_intersection.y][map_intersection.x] == '1')
		{
			return (true);
			printf("HIT WALL: a_y: %f a_x: %f\n", a_y, a_x);
		}
		draw_line((t_vector2dint){position.x * TILE_SIZE, position.y * TILE_SIZE}, \
		circle_line, minimap, PINK);
		i += RADIAN;
	}
	return (false);
}

void	move_player(void *param)
{
	t_game	*game;
	t_vector2d	new_position;
	float	x_change;
	float	y_change;

	game = (t_game *)param;
	new_position = (t_vector2d){game->player.x, game->player.y};
	x_change = 0;
	y_change = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		y_change += -MOVE_STEPS;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		y_change += MOVE_STEPS;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		x_change += -MOVE_STEPS;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		x_change += MOVE_STEPS;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		move_angle_left(&game->player);
		set_ray_angles(game->player.rays, &game->player);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		move_angle_right(&game->player);
		set_ray_angles(game->player.rays, &game->player);
	}
	if (x_change != 0 && y_change != 0)
	{
		normalize_vector(&x_change, &y_change);
	}
	new_position.x += x_change * game->mlx->delta_time;
	new_position.y += y_change * game->mlx->delta_time;
	if (!collide_circle(new_position, &game->map, 0.3, game->minimap))
	{
		game->player.x = new_position.x;
		game->player.y = new_position.y;
	}
	// game->player.x += x_change * game->mlx->delta_time;
	// game->player.y += y_change * game->mlx->delta_time;
}

