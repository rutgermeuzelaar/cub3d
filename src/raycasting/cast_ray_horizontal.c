/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_horizontal.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 14:53:15 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/19 16:05:35 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "player.h"
#include "map.h"
#include "minimap.h"
#include "raycasting.h"

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
	progress_collision(&collision, map, ray->cardinal, \
	(t_vector2d){(atan * -TILE_SIZE), TILE_SIZE});
	return (collision);
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
	progress_collision(&collision, map, ray->cardinal, \
	(t_vector2d){(atan * TILE_SIZE), -TILE_SIZE});
	return (collision);
}

t_ray_collision	get_ray_collision_horizontal(t_ray *ray, t_map *map)
{
	t_ray_collision	collision;

	if (ray->angle > M_PI)
	{
		ray->cardinal = SOUTH;
		collision = get_ray_collision_down(ray, map);
	}
	if (ray->angle < M_PI)
	{
		ray->cardinal = NORTH;
		collision = get_ray_collision_up(ray, map);
	}
	ray->direction = collision.point;
	set_ray_distance(ray, &collision);
	return (collision);
}
