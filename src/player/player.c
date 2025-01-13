/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 16:20:18 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/13 15:28:36 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "shapes.h"
#include "libft.h"
#include "player.h"
#include "utilities.h"
#include "map.h"
#include "MLX42/MLX42.h"
#include "minimap.h"

void	init_player(t_player *const player, float spawn_x, float spawn_y)
{
	player->color.rgba = get_rgba(0xfc0fc0, 255);
	player->ray_color.rgba = get_rgba(0xDC143C, 255);
	player->x = spawn_x;
	player->y = spawn_y;
	player->rectangle.height = 16;
	player->rectangle.width = 16;
	player->rectangle.x = 50;
	player->rectangle.y = 50;
	player->dir.height = 4;
	player->dir.width = 4;
	player->dir.x = 50;
	player->dir.y = 50;
	player->dir_angle = 0;
	ft_memset(&player->ray, 0, sizeof(t_ray));
}

void	draw_player(const t_player *const player, mlx_image_t *minimap)
{
	draw_rectangle(minimap, (t_rectangle){player->x - \
	(player->rectangle.width / 2), player->y - (player->rectangle.height / 2), \
	player->rectangle.width, player->rectangle.height}, player->color.rgba);
	draw_line(player->x, \
	player->y, player->dir.x, \
	player->dir.y, minimap, player->color.rgba);
}
