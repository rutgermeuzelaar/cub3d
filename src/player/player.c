/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 16:20:18 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/19 00:26:13 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "shapes.h"
#include "libft.h"
#include "player.h"
#include "utilities.h"
#include "map.h"
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "raycasting.h"

static void	elden(t_ray *rays, const int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("rays[i] ANGLE: %f\n", rays[i].angle);
		i++;
	}
}

bool	init_player(t_player *const player, float spawn_x, float spawn_y)
{
	player->ray_count = 5;
	player->rays = ft_calloc(player->ray_count, sizeof(t_ray));
	if (!player->rays)
	{
		return (false);
	}
	player->color.rgba = get_rgba(0xfc0fc0, 255);
	player->ray_color.rgba = get_rgba(0xfff0f5, 255);
	player->x = spawn_x;
	player->y = spawn_y;
	player->height = 16;
	player->width = 16;
	player->dir_angle = 0;
	set_ray_angles(player->rays, player);
	elden(player->rays, player->ray_count);
	player->dir_x = cos(player->dir_angle);
	player->dir_y = sin(player->dir_angle);
	return (true);	
}

void	draw_player(const t_player *const player, mlx_image_t *minimap)
{
	t_vector2dint	direction;

	direction.x = player->x + (player->dir_x * 5);
	direction.y = player->y + (player->dir_y * 5);
	draw_rectangle(minimap, (t_rectangle){player->x - \
	(player->width / 2), player->y - (player->height / 2), \
	player->width, player->height}, player->color.rgba);
	draw_line((t_vector2dint){player->x, player->y}, \
	direction, minimap, player->color.rgba);
}
