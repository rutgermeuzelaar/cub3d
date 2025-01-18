/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 16:20:18 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/18 15:03:25 by rmeuzela      ########   odam.nl         */
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
	player->dir_angle = 0;
	player->dir_x = cos(player->dir_angle);
	player->dir_y = sin(player->dir_angle);
	ft_memset(&player->ray, 0, sizeof(t_ray));
}

void	draw_player(const t_player *const player, mlx_image_t *minimap)
{
	t_vector2dint	direction;

	direction.x = player->x + (player->dir_x * 5);
	direction.y = player->y + (player->dir_y * 5);
	draw_rectangle(minimap, (t_rectangle){player->x - \
	(player->rectangle.width / 2), player->y - (player->rectangle.height / 2), \
	player->rectangle.width, player->rectangle.height}, player->color.rgba);
	draw_line((t_vector2dint){player->x, player->y}, \
	direction, minimap, player->color.rgba);
}
