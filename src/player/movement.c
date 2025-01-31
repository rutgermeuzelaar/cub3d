/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 15:06:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/31 12:58:04 by rmeuzela      ########   odam.nl         */
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
		}
		draw_line((t_vector2dint){position.x * TILE_SIZE, position.y * TILE_SIZE}, \
		circle_line, minimap, PINK);
		i += RADIAN;
	}
	return (false);
}

typedef void (*move_func)(mlx_t *, float *, float *);

t_vector2dint	set_direction_vector(mlx_t *mlx)
{
	t_vector2dint	direction;

	direction.x = 0;
	direction.y = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		direction.y -= 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		direction.y += 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		direction.x -= 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		direction.x += 1;
	}
	return (direction);
}

t_cardinal_direction	get_cardinal(t_vector2dint direction_vector)
{
	t_cardinal_direction	cardinal;

	if (direction_vector.x == 0 && direction_vector.y == 0)
	{
		cardinal = CARDINAL_NONE;
		return (cardinal);
	}
	if (direction_vector.x == 0 && direction_vector.y != 0)
	{
		if (direction_vector.y == -1)
		{
			cardinal = NORTH;
		}
		else
		{
			cardinal = SOUTH;
		}
		return (cardinal);
	}
	if (direction_vector.y == 0 && direction_vector.x != 0)
	{
		if (direction_vector.x == -1)
		{
			cardinal = WEST;
		}
		else
		{
			cardinal = EAST;
		}
		return (cardinal);
	}
	if (direction_vector.y == -1)
	{
		if (direction_vector.x == -1)
		{
			cardinal = NORTH_WEST;
		}
		else
		{
			cardinal = NORTH_EAST;
		}
		return (cardinal);
	}
	else
	{
		if (direction_vector.x == -1)
		{
			cardinal = SOUTH_WEST;
		}
		else
		{
			cardinal = SOUTH_EAST;
		}
	}
	return (cardinal);
}

t_vector2d	get_new_position(t_cardinal_direction cardinal, float angle, \
			t_vector2d position, const float delta_time)
{
	const float	quarter = RADIAN * 45;
	const float	radius = MOVE_STEPS * delta_time;
	t_vector2d	circle_point_1;
	t_vector2d 	circle_point_2;

	circle_point_1 = position;
	circle_point_2 = position;
	if (cardinal == NORTH || cardinal == SOUTH)
	{
		circle_point_1.x += cos(angle) * radius;
		circle_point_1.y += sin(angle) * radius;
		if (cardinal == NORTH)
		{
			return (circle_point_1);
		}
		circle_point_2.x += position.x - circle_point_1.x;
		circle_point_2.y += position.y - circle_point_1.y;
		return (circle_point_2);
	}
	if (cardinal == NORTH_EAST || cardinal == SOUTH_WEST)
	{
		circle_point_1.x += cos(angle + quarter) * radius;
		circle_point_1.y += sin(angle + quarter) * radius;
		if (cardinal == NORTH_EAST)
		{
			return (circle_point_1);
		}
		circle_point_2.x += position.x - circle_point_1.x;
		circle_point_2.y += position.y - circle_point_1.y;
		return (circle_point_2);
	
	}
	if (cardinal == EAST || cardinal == WEST)
	{
		circle_point_1.x += cos(angle + (quarter * 2)) * radius;
		circle_point_1.y += sin(angle + (quarter * 2)) * radius;
		if (cardinal == EAST)
		{
			return (circle_point_1);
		}
		circle_point_2.x += position.x - circle_point_1.x;
		circle_point_2.y += position.y - circle_point_1.y;
		return (circle_point_2);
	}
	if (cardinal == SOUTH_EAST || cardinal == NORTH_WEST)
	{	
		circle_point_1.x += cos(angle + (quarter * 3)) * radius;
		circle_point_1.y += sin(angle + (quarter * 3)) * radius;
		if (cardinal == SOUTH_EAST)
		{
			return (circle_point_1);
		}
		circle_point_2.x += position.x - circle_point_1.x;
		circle_point_2.y += position.y - circle_point_1.y;
		return (circle_point_2);
	}
	return (position);
}

void	move_player(void *param) 
{
	t_game			*game;
	t_vector2d		new_position;
	t_vector2dint	direction;
	t_cardinal_direction	cardinal;

	game = (t_game *)param;
	new_position = (t_vector2d){game->player.x, game->player.y};
	direction = set_direction_vector(game->mlx);
	cardinal = get_cardinal(direction);
	new_position = get_new_position(cardinal, game->player.dir_angle, (t_vector2d){game->player.x, game->player.y}, \
	game->mlx->delta_time);
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
	if (!collide_circle(new_position, &game->map, 0.3, game->minimap))
	{
		game->player.x = new_position.x;
		game->player.y = new_position.y;
	}
}
