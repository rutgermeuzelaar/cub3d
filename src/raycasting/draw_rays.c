/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:45:51 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/10 13:26:46 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "player.h"
#include "map.h"
#include "shapes.h"

// void	draw_ray(t_player *player, t_map *map, mlx_image_t *minimap, t_ray *ray)
// {
// 	int				i;
// 	t_vector2dint	map_point;
// 	float			ray_x_offset;
// 	float			ray_y_offset;
// 	float			a_tan;

// 	i = 0;
// 	a_tan = -1/tan(player->dir_angle);
// 	printf("a_tan: %f\n", a_tan);
// 	ray->position.x = player->x;
// 	ray->position.y = player->y;
// 	// horizontal
// 	// looking up
// 	(void)map;
// 	(void)minimap;
// 	if (player->dir_angle > M_PI)
// 	{
// 		ray->direction.y = (((int)player->y>>6)<<6)-0.0001;
// 		ray->direction.x = (ray->position.y - ray->direction.y) * a_tan + ray->position.x;
// 		ray_y_offset = -TILE_SIZE;
// 		ray_x_offset = -ray_y_offset * a_tan;
// 	}
// 	printf("ray->direction.y: %f ray->direction.x: %f ray_y_offset: %f ray_x_offset: %f\n\n", ray->direction.y, ray->direction.x, ray_y_offset, \
// 	ray_x_offset);
// 	if (player->dir_angle == 0 || player->dir_angle == M_PI)
// 	{
// 		ray->direction.y = player->y;
// 		ray->direction.x = player->x;
// 		i = 5;
// 	}
// 	while (i < 6)
// 	{
// 		map_point.x = ray->direction.y / TILE_SIZE;
// 		map_point.y = ray->direction.x / TILE_SIZE;
// 		printf("map_point.x: %d map_point.y: %d\n", map_point.x, map_point.y);
// 		if ((size_t)map_point.x > map->width - 1 || (size_t)map_point.y > map->height - 1)
// 		{
// 			break ;
// 		}
// 		if (map_point.x < 0 || map_point.y < 0)
// 		{
// 			break;
// 		}
// 		if (map->map[map_point.y][map_point.x] == '1')
// 		{
// 			break ;
// 		}
// 		ray->direction.y += ray_y_offset;
// 		ray->direction.x += ray_x_offset;
// 		i++;
// 	}
// 	draw_line(ray->position.x, ray->position.y, ray->direction.x, \
// 	ray->direction.y, minimap, get_rgba(0x00ff00, 255));
// 	// looking down
// }

