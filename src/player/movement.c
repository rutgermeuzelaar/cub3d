/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 15:06:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/18 20:09:29 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "cub3d.h"

typedef void (*move_func)(float *point, double delta_time, uint32_t limit);

static void	move_up(float *y, double delta_time, uint32_t min)
{
	*y -= MOVE_STEPS * delta_time;
	if (*y <= min)
	{
		*y = min;
	}
}

static void move_down(float *y, double delta_time, uint32_t max)
{
	*y += MOVE_STEPS * delta_time;
	if (*y >= max)
	{
		*y = max;
	}
}

static void move_left(float *x, double delta_time, uint32_t min)
{
	*x -= MOVE_STEPS * delta_time;
	if (*x <= min)
	{
		*x = min;
	}
}

static void move_right(float *x, double delta_time, uint32_t max)
{
	*x += MOVE_STEPS * delta_time;
	if (*x >= max)
	{
		*x = max;
	}
}

void	move_angle_right(t_player *player)
{
	player->dir_angle += ROTATION_SPEED;
	if (player->dir_angle >= (2 * M_PI))
	{
		player->dir_angle -= 2 * M_PI;
	}
	player->dir_x = cos(player->dir_angle) * DIRECTION_LINE_LENGTH;
	player->dir_y = sin(player->dir_angle) * DIRECTION_LINE_LENGTH;
}

void	move_angle_left(t_player *player)
{
	player->dir_angle -= ROTATION_SPEED;
	if (player->dir_angle <= 0)
	{
		player->dir_angle += 2 * M_PI;
	}
	player->dir_x = cos(player->dir_angle) * DIRECTION_LINE_LENGTH;
	player->dir_y = sin(player->dir_angle) * DIRECTION_LINE_LENGTH;
}

void	move_player_up(t_player *player, t_map *map, float delta_time)
{
	const float	new_y = player->y - (MOVE_STEPS * delta_time);

	if (is_colliding((t_vector2d){player->x, new_y}, map))
	{
		return ;
	}
	player->y = new_y;
}

void	move_player(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	const uint32_t	x_left_offset = game->player.rectangle.width / 2;
	const uint32_t	x_right_offset = game->minimap->width - \
					(game->player.rectangle.width / 2);
	const uint32_t	y_up_offset = game->player.rectangle.height / 2;
	const uint32_t	y_down_offset = game->minimap->height - \
					(game->player.rectangle.height / 2);
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		move_player_up(&game->player, &game->map, game->mlx->delta_time);
		// move_up(&game->player.y, game->mlx->delta_time, y_up_offset);
		move_up(&game->player.rectangle.y, game->mlx->delta_time, y_up_offset);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		move_down(&game->player.y, game->mlx->delta_time, y_down_offset);
		move_down(&game->player.rectangle.y, game->mlx->delta_time, y_down_offset);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_left(&game->player.x, game->mlx->delta_time, x_left_offset);
		move_left(&game->player.rectangle.x, game->mlx->delta_time, x_left_offset);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_right(&game->player.x, game->mlx->delta_time, x_right_offset);
		move_right(&game->player.rectangle.x, game->mlx->delta_time, x_right_offset);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		move_angle_left(&game->player);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		move_angle_right(&game->player);
	}
}
