/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 15:06:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/31 14:17:12 by rmeuzela      ########   odam.nl         */
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
	const t_vector2dint	cardinal_all[CARDINAL_COUNT] = {
	[SOUTH] = (t_vector2dint){0, 1},
	[NORTH] = (t_vector2dint){0, -1},
	[EAST] = (t_vector2dint){1, 0},
	[WEST] = (t_vector2dint){-1, 0},
	[NORTH_EAST] = (t_vector2dint){1, -1},
	[SOUTH_WEST] = (t_vector2dint){-1, 1},
	[SOUTH_EAST] = (t_vector2dint){1, 1},
	[NORTH_WEST] = (t_vector2dint){-1, -1},
	};
	int					i;

	i = 0;
	if (direction_vector.x == 0 && direction_vector.y == 0)
	{
		return (CARDINAL_NONE);
	}
	while (i < CARDINAL_COUNT)
	{
		if (direction_vector.x == cardinal_all[i].x && \
		direction_vector.y == cardinal_all[i].y)
			return (i);
		i++;
	}
	return (CARDINAL_NONE);
}

static float	get_movement_angle(t_cardinal_direction cardinal, \
				const float angle)
{
	const float	quarter = RADIAN * 45;

	if (cardinal == NORTH || cardinal == SOUTH)
	{
		return (angle);
	}
	if (cardinal == NORTH_EAST || cardinal == SOUTH_WEST)
	{
		return (angle + quarter);
	}
	if (cardinal == EAST || cardinal == WEST)
	{
		return (angle + quarter * 2);
	}
	if (cardinal == SOUTH_EAST || cardinal == NORTH_WEST)
	{
		return (angle + quarter * 3);
	}
	return (angle);
}

t_vector2d	get_new_position(t_cardinal_direction cardinal, float angle, \
			t_vector2d position, const float delta_time)
{
	const float	radius = MOVE_STEPS * delta_time;
	t_vector2d	circle_point_1;
	t_vector2d	circle_point_2;

	circle_point_1 = position;
	circle_point_2 = position;
	circle_point_1.x += cos(angle) * radius;
	circle_point_1.y += sin(angle) * radius;
	if (cardinal == CARDINAL_NONE)
	{
		return (position);
	}
	if (cardinal == NORTH || cardinal == NORTH_EAST || cardinal == EAST || \
	cardinal == SOUTH_EAST)
	{
		return (circle_point_1);
	}
	circle_point_2.x += position.x - circle_point_1.x;
	circle_point_2.y += position.y - circle_point_1.y;
	return (circle_point_2);
}

void	move_player(void *param)
{
	t_game *const				game = (t_game *)param;
	const t_vector2dint			direction = set_direction_vector(game->mlx);
	const t_cardinal_direction	cardinal = get_cardinal(direction);
	const float					angle = get_movement_angle(cardinal, \
								game->player.dir_angle);
	const t_vector2d			new_position = \
								get_new_position(cardinal, angle, \
								(t_vector2d){game->player.x, game->player.y}, \
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
	if (!collide_circle(new_position, &game->map, 0.05))
	{
		game->player.x = new_position.x;
		game->player.y = new_position.y;
	}
}
