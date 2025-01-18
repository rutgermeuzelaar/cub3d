/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_horizontal.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 14:53:15 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/19 00:19:29 by rmeuzela      ########   odam.nl         */
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

static void loop_collision_up(t_ray_collision *collision, t_map *map, \
			float y_step, float x_step)
{
	const uint32_t	height = map->height * TILE_SIZE;
	const uint32_t	width = map->width * TILE_SIZE;
	t_vector2dint	map_intersect;

	while (!point_out_of_bounds(&collision->point, height, width))
	{
		map_intersect.x = collision->point.x / TILE_SIZE;
		map_intersect.y = collision->point.y / TILE_SIZE;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			break ;
		}
		collision->point.x -= x_step;
		collision->point.y -= y_step;
	}
}

static t_ray_collision get_ray_collision_up(t_ray *ray, t_map *map)
{
	const float 	closest_y = ceil_multiple(ray->position.y, TILE_SIZE);
	const float 	delta_y = ray->position.y - closest_y;
	float			atan;
	t_ray_collision	collision;

	collision.point = ray->position;
	collision.point.y = closest_y;
	atan = -1 / tan(ray->angle);
	collision.point.x = (delta_y * atan) + ray->position.x;
	loop_collision_up(&collision, map, -TILE_SIZE, (atan * TILE_SIZE));
	return (collision);
}

static void loop_collision_down(t_ray_collision *collision, t_map *map, \
			float y_step, float x_step)
{
	const uint32_t	height = map->height * TILE_SIZE;
	const uint32_t	width = map->width * TILE_SIZE;
	t_vector2dint	map_intersect;

	while (!point_out_of_bounds(&collision->point, height, width))
	{
		map_intersect.x = collision->point.x / TILE_SIZE;
		map_intersect.y = collision->point.y / TILE_SIZE - 0.1f;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			collision->hit = true;
			break ;
		}
		collision->point.x -= x_step;
		collision->point.y -= y_step;
	}
}

static t_ray_collision	get_ray_collision_down(t_ray *ray, t_map *map)
{
	const float 	closest_y = floor_multiple(ray->position.y, TILE_SIZE);
	const float 	delta_y = ray->position.y - closest_y;
	float			atan;
	t_ray_collision	collision;

	collision.point = ray->position;
	collision.point.y = closest_y;
	atan = -1 / tan(ray->angle);
	collision.point.x = (delta_y * atan) + ray->position.x;
	loop_collision_down(&collision, map, TILE_SIZE, (atan * -TILE_SIZE));
	return (collision);
}

t_ray_collision	get_ray_collision_horizontal(t_ray *ray, t_map *map, mlx_image_t *minimap)
{
	t_ray_collision	collision;

	(void)minimap;
	if (ray->angle > M_PI)
	{
		collision = get_ray_collision_down(ray, map);
	}
	if (ray->angle < M_PI)
	{
		collision = get_ray_collision_up(ray, map);
	}
	ray->direction = collision.point;
	set_ray_distance(ray, &collision);
	return (collision);
}
