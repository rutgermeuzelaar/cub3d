/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_horizontal.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 14:53:15 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/17 18:14:36 by rmeuzela      ########   odam.nl         */
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
#include "raycasting.h"

static void get_ray_hit_up(t_ray *ray, t_map *map, float y_step, float x_step)
{
	const uint32_t	height = map->height * TILE_SIZE;
	const uint32_t	width = map->width * TILE_SIZE;
	t_vector2dint	map_intersect;

	while (!point_out_of_bounds(&ray->direction, height, width))
	{
		map_intersect.x = ray->direction.x / TILE_SIZE;
		map_intersect.y = ray->direction.y / TILE_SIZE;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			break ;
		}
		ray->direction.x -= x_step;
		ray->direction.y -= y_step;
	}
}

static void	cast_ray_up(t_ray *ray, t_player *player, t_map *map, 
			mlx_image_t *minimap)
{
	const float closest_y = player->y - ((int)player->y % TILE_SIZE);
	const float delta_y = player->y - closest_y;
	float		x_step;
	
	ray->position.x = player->x;
	ray->position.y = player->y;
	ray->direction = ray->position;
	x_step = -1 / tan(player->dir_angle);
	ray->direction.x += (x_step * delta_y);
	ray->direction.y -= delta_y;
	get_ray_hit_up(ray, map, -TILE_SIZE, x_step * TILE_SIZE);
	draw_line((t_vector2dint){ray->position.x, ray->position.y}, \
	(t_vector2dint){ray->direction.x, ray->direction.y}, 
	minimap, get_rgba(0x87ceeb, 255));
}

static void get_ray_hit_down(t_ray *ray, t_map *map, float y_step, float x_step)
{
	const uint32_t	height = map->height * TILE_SIZE;
	const uint32_t	width = map->width * TILE_SIZE;
	t_vector2dint	map_intersect;

	while (!point_out_of_bounds(&ray->direction, height, width))
	{
		map_intersect.x = ray->direction.x / TILE_SIZE;
		map_intersect.y = ray->direction.y / TILE_SIZE - 0.1f;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			break ;
		}
		ray->direction.x -= x_step;
		ray->direction.y += y_step;
	}
}

static void	cast_ray_down(t_ray *ray, t_player *player, t_map *map, 
			mlx_image_t *minimap)
{
	const float closest_y = player->y - ((int)player->y % TILE_SIZE);
	const float delta_y = TILE_SIZE - (player->y - closest_y);
	float		x_step;

	ray->position.x = player->x;
	ray->position.y = player->y;
	ray->direction = ray->position;
	x_step = -1 / tan(player->dir_angle);
	ray->direction.x -= (x_step * delta_y);
	ray->direction.y += delta_y;
	get_ray_hit_down(ray, map, -TILE_SIZE, -(x_step * TILE_SIZE));
	printf("closest_y: %f\n", closest_y);
	printf("ray_dir_x: %f ray_dir_y: %f\n", ray->direction.x, ray->direction.y);
	draw_line((t_vector2dint){ray->position.x, ray->position.y}, \
	(t_vector2dint){ray->direction.x, ray->direction.y}, 
	minimap, get_rgba(0x61DE2A, 255));
}

void	cast_ray_horizontal(t_ray *ray, t_player *player, t_map *map, 
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
