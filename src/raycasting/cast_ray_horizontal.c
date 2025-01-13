/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_horizontal.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 14:53:15 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/13 17:45:24 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "player.h"
#include "map.h"
#include "minimap.h"

static void get_ray_hit(t_ray *ray, t_map *map, float y_step, float x_step)
{
	t_vector2dint	map_intersect;
	int				i;
	
	i = 0;
	// printf("y_step: %f, x_step: %f\n", y_step, x_step);
	while (i < 2)
	{
		map_intersect.x = (ray->direction.x - ((int)ray->direction.x % TILE_SIZE)) / TILE_SIZE;
		map_intersect.y = (ray->direction.y - ((int)ray->direction.x % TILE_SIZE)) / TILE_SIZE;
		printf("map_intersect.x: %d map_intersect.y: %d\n", map_intersect.x, map_intersect.y);
		// printf("ray_dir_x: %f ray_dir_y: %f\n", ray->direction.x, ray->direction.y);
		if (map_intersect.x < 0 || (size_t)map_intersect.x > (map->width))
		{
			ray->direction.x += x_step;
			break ;
		}
		if (map_intersect.y < 0 || (size_t)map_intersect.y > (map->height))
		{
			ray->direction.y += y_step;
			break ;
		}
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			printf("HIT HORIZONTAL WALL\n");
			break ;
		}
		// check if wall is hit
		ray->direction.y += y_step;
		ray->direction.x += x_step;
		i++;
	}
}

static void	cast_ray_up(t_ray *ray, t_player *player, t_map *map, \
			mlx_image_t *minimap)
{
	const float closest_y = player->y - ((int)player->y % TILE_SIZE);
	const float delta_y = player->y - closest_y;
	float		delta_x;
	float		cheese;
	
	(void)map;
	(void)minimap;
	ray->position.x = player->x;
	ray->position.y = player->y;
	ray->direction = ray->position;
	delta_x = -delta_y / tan(player->dir_angle);
	cheese = -1 / tan(player->dir_angle);
	assert(delta_x != -INFINITY && delta_x != -NAN);
	ray->direction.x += delta_x;
	ray->direction.y -= delta_y;
	draw_line(player->x, player->y, player->x + delta_x, player->y, minimap, get_rgba(0xFFD700, 255));
	draw_line(player->x + delta_x, player->y - delta_y, player->x + delta_x, player->y, minimap, get_rgba(0xFFD700, 255));
	draw_line(player->x, player->y, player->x + delta_x, player->y - delta_y, minimap, get_rgba(0xFFD700, 255));
	get_ray_hit(ray, map, -TILE_SIZE, cheese * TILE_SIZE);
	draw_line(ray->position.x, ray->position.y, ray->direction.x, ray->direction.y, \
	minimap, get_rgba(0x87ceeb, 255));
	return ;
}

static void	cast_ray_down(t_ray *ray, t_player *player, t_map *map, \
			mlx_image_t *minimap)
{
	(void)ray;
	(void)player;
	(void)map;
	(void)minimap;
}

void	cast_ray_horizontal(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap)
{
	if (player->dir_angle > M_PI)
	{
		cast_ray_down(ray, player, map, minimap);
	}
	if (player->dir_angle < M_PI)
	{
		cast_ray_up(ray, player, map, minimap);
	}
}
