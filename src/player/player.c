/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 16:20:18 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/03 01:20:57 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "shapes.h"
#include "player.h"
#include "utilities.h"
#include "MLX42/MLX42.h"

void	init_player(t_player *const player)
{
	player->color = get_rgba(0xfc0fc0, 255);
	player->rectangle.height = 16;
	player->rectangle.width = 16;
	player->rectangle.x = 50;
	player->rectangle.y = 50;
	player->dir.height = 4;
	player->dir.width = 4;
	player->dir.x = 50;
	player->dir.y = 10;
	player->dir_angle = M_PI/2;
}

void	draw_player(const t_player *const player, mlx_image_t *minimap)
{
	draw_rectangle(minimap, player->rectangle, player->color);
	draw_rectangle(minimap, player->dir, player->color);
	draw_line(player->rectangle.x, player->rectangle.y, player->dir.x, \
	player->dir.y,minimap, player->color);
}
