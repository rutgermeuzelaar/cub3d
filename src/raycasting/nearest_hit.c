/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nearest_hit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:46:01 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/10 16:28:21 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "player.h"
#include "map.h"
#include "minimap.h"

t_vector2d	get_nearest_hit(t_player *player, t_map *map, float angle, \
			mlx_image_t *minimap)
{
	const float closest_y = player->y - ((int)player->y % TILE_SIZE);
	const float closest_x = player->x - ((int)player->x % TILE_SIZE);
	const float delta_y = player->y - closest_y;
	float		delta_x;

	(void)map;
	(void)minimap;
	(void)closest_x;
	if (angle > M_PI)
	{
		return ((t_vector2d){0, 0});
	}
	delta_x = -delta_y / tan(angle);
	printf("player->x: %f, player->y: %f\n", player->x, player->y);
	printf("closest_y: %f delta_y: %f delta_x: %f\n", closest_y, delta_y, delta_x);
	printf("delta_x: %f delta_y: %f\n\n", delta_x, delta_y);
	if (delta_x == -INFINITY || delta_x == -NAN)
	{
		printf("illegal\n");
		return ((t_vector2d){0, 0});
	}
	draw_line(player->x, player->y, player->x + delta_x, player->y, minimap, get_rgba(0xFFD700, 255));
	draw_line(player->x + delta_x, player->y - delta_y, player->x + delta_x, player->y, minimap, get_rgba(0xFFD700, 255));
	draw_line(player->x, player->y, player->x + delta_x, player->y - delta_y, minimap, get_rgba(0xFFD700, 255));
	return ((t_vector2d){0, 0});
}

// void	draw_along_square(t_player *player, t_map *map, mlx_image_t *minimap)
// {
	
// }
// check if player is looking up
// check if player is looking down