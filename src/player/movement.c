/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 15:06:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/01 22:46:24 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "MLX42/MLX42.h"
#include "cub3d.h"

void	move_player(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player.rectangle.y -= MOVE_STEPS * game->mlx->delta_time;
		if (game->player.rectangle.y <= 0)
		{
			game->player.rectangle.y = 0;
		}
		printf("GO UP!\n");
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player.rectangle.y += MOVE_STEPS * game->mlx->delta_time;
		if (game->player.rectangle.y >= game->minimap->height - game->player.rectangle.height)
		{
			game->player.rectangle.y = game->minimap->height - game->player.rectangle.height;
		}
		printf("GO DOWN!\n");
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player.rectangle.x -= MOVE_STEPS * game->mlx->delta_time;
		if (game->player.rectangle.x <= 0)
		{
			game->player.rectangle.x = 0;
		}
		printf("GO LEFT!\n");
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player.rectangle.x += MOVE_STEPS * game->mlx->delta_time;
		if (game->player.rectangle.x >= game->minimap->width - \
		game->player.rectangle.width)
		{
			game->player.rectangle.x = game->minimap->width - \
			game->player.rectangle.width;
		}
		printf("GO RIGHT!\n");
	}
}
