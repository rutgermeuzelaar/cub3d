/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 15:06:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/20 15:23:47 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <stdio.h>
#include <math.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "cub3d.h"
#include "raycasting.h"

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

void	move_player(void *param)
{
	t_game	*game;
	float	x_change;
	float	y_change;

	game = (t_game *)param;
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
	game->player.x += x_change * game->mlx->delta_time;
	game->player.y += y_change * game->mlx->delta_time;
}
