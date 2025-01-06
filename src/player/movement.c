/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 15:06:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/06 20:29:18 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "cub3d.h"

typedef void (*move_func)(float *, float *, double);

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

void	move_dir_right(t_player *player)
{
	player->dir_angle += ROTATION_SPEED;
	if (player->dir_angle >= (2 * M_PI))
	{
		player->dir_angle -= 2 * M_PI;
	}
	player->dir.x = player->rectangle.x + (cos(player->dir_angle) * DIRECTION_LINE_LENGTH);
	player->dir.y = player->rectangle.y + (sin(player->dir_angle) * DIRECTION_LINE_LENGTH);
}

void	move_dir_left(t_player *player)
{
	player->dir_angle -= ROTATION_SPEED;
	if (player->dir_angle <= 0)
	{
		player->dir_angle += 2 * M_PI;
	}
	player->dir.x = player->rectangle.x + (cos(player->dir_angle) * DIRECTION_LINE_LENGTH);
	player->dir.y = player->rectangle.y + (sin(player->dir_angle) * DIRECTION_LINE_LENGTH);
}

void	move_player(void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		move_up(&game->player.rectangle.y, game->mlx->delta_time, 0);
		move_up(&game->player.dir.y, game->mlx->delta_time, 0);
		printf("GO UP!\n");
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		move_down(&game->player.rectangle.y, game->mlx->delta_time, \
		game->minimap->height - game->player.rectangle.height);
		move_down(&game->player.dir.y, game->mlx->delta_time, \
		game->minimap->height - game->player.rectangle.height);
		printf("GO DOWN!\n");
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_left(&game->player.rectangle.x, game->mlx->delta_time, 0);
		move_left(&game->player.dir.x, game->mlx->delta_time, 0);
		printf("GO LEFT!\n");
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_right(&game->player.rectangle.x, game->mlx->delta_time, \
		game->minimap->width - game->player.rectangle.width);
		move_right(&game->player.dir.x, game->mlx->delta_time, \
		game->minimap->width - game->player.rectangle.width);
		printf("GO RIGHT!\n");
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		move_dir_left(&game->player);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		move_dir_right(&game->player);
	}
}
