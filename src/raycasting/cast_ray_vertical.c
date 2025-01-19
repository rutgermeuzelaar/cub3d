/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_vertical.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 22:55:55 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/19 16:16:56 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>
#include "shapes.h"
#include "player.h"
#include "map.h"
#include "minimap.h"
#include "raycasting.h"

static t_ray_collision	get_ray_collision_right(t_ray *ray, t_map *map)
{
	const float 	closest_x = ray->position.x - ((int)ray->position.x % TILE_SIZE);
	const float 	delta_x = TILE_SIZE - (ray->position.x - closest_x);
	float			y_step;
	t_ray_collision	collision;

	collision.point = ray->position;
	y_step = -1 * tan(ray->angle);
	collision.point.x += delta_x;
	collision.point.y -= (y_step * delta_x);
	progress_collision(&collision, map, ray->cardinal, \
	(t_vector2d){TILE_SIZE, y_step * -TILE_SIZE});
	return (collision);
}

static t_ray_collision	get_ray_collision_left(t_ray *ray, t_map *map)
{
	const float 	closest_x = ray->position.x - ((int)ray->position.x % \
					TILE_SIZE);
	const float 	delta_x = ray->position.x - closest_x;
	float			y_step;
	t_ray_collision	collision;

	collision.point = ray->position;
	y_step = -1 * tan(ray->angle);
	collision.point.x -= delta_x;
	collision.point.y += (y_step * delta_x);
	progress_collision(&collision, map, ray->cardinal, \
	(t_vector2d){-TILE_SIZE, (y_step * TILE_SIZE)});
	return (collision);
}

t_ray_collision	get_ray_collision_vertical(t_ray *ray, t_map *map)
{
	t_ray_collision	collision;

	if (ray->angle < M_PI_2 || ray->angle > ((3 * M_PI) / 2))
	{
		ray->cardinal = EAST;
		collision = get_ray_collision_right(ray, map);
	}
	if (ray->angle > M_PI_2 && ray->angle < ((3 * M_PI) / 2))
	{
		ray->cardinal = WEST;
		collision = get_ray_collision_left(ray, map);
	}
	ray->direction = collision.point;
	set_ray_distance(ray, &collision);
	return (collision);
}
