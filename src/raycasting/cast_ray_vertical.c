/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_vertical.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 22:55:55 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/19 14:43:03 by rmeuzela      ########   odam.nl         */
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

static void get_ray_hit_right(t_ray *ray, t_map *map, float y_step, float x_step)
{
	const uint32_t	height = map->height * TILE_SIZE;
	const uint32_t	width = map->width * TILE_SIZE;
	t_vector2dint	map_intersect;

	while (!point_out_of_bounds(&ray->direction, height, width))
	{
		map_intersect.x = ray->direction.x / TILE_SIZE + 0.1f;
		map_intersect.y = ray->direction.y / TILE_SIZE;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			break ;
		}
		ray->direction.x += x_step;
		ray->direction.y -= y_step;
	}
}

static void	loop_collision_right(t_ray_collision *collision, \
			t_map *map, float y_step, float x_step)
{
	const uint32_t	height = map->height * TILE_SIZE;
	const uint32_t	width = map->width * TILE_SIZE;
	t_vector2dint	map_intersect;

	while (!point_out_of_bounds(&collision->point, height, width))
	{
		map_intersect.x = collision->point.x / TILE_SIZE + 0.1f;
		map_intersect.y = collision->point.y / TILE_SIZE;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			break ;
		}
		collision->point.x += x_step;
		collision->point.y -= y_step;
	}
}

static void	cast_ray_right(t_ray *ray, t_player *player, t_map *map, 
			mlx_image_t *minimap)
{
	const float closest_x = player->x - ((int)player->x % TILE_SIZE);
	const float delta_x = TILE_SIZE - (player->x - closest_x);
	float		y_step;

	ray->position.x = player->x;
	ray->position.y = player->y;
	ray->direction = ray->position;
	y_step = -1 * tan(player->dir_angle);
	if (y_step == -INFINITY)
	{
		return ;
	}
	ray->direction.x += delta_x;
	ray->direction.y -= (y_step * delta_x);
	if (y_step == -INFINITY)
	{
		printf("aa\n");
		return ;
	}
	get_ray_hit_right(ray, map, y_step * TILE_SIZE, TILE_SIZE);
	draw_line((t_vector2dint){ray->position.x, ray->position.y}, 
	(t_vector2dint){ray->direction.x, ray->direction.y}, 
	minimap, get_rgba(0x9400d3, 255));
}

static t_ray_collision	get_ray_collision_right(t_ray *ray, t_map *map)
{
	const float 	closest_x = ray->position.x - ((int)ray->position.x % TILE_SIZE);
	const float 	delta_x = TILE_SIZE - (ray->position.x - closest_x);
	float			y_step;
	t_ray_collision	collision;

	collision.point = ray->position;
	y_step = -1 * tan(ray->angle);
	printf("y_step: %f\n", y_step);
	if (y_step == -INFINITY)
	{
		return collision;
	}
	collision.point.x += delta_x;
	collision.point.y -= (y_step * delta_x);
	// if (y_step == -INFINITY)
	// {
	// 	return ;
	// }
	loop_collision_right(&collision, map, y_step * TILE_SIZE, TILE_SIZE);
	return (collision);
}

static void get_ray_hit_left(t_ray *ray, t_map *map, float y_step, float x_step)
{
	const uint32_t	height = map->height * TILE_SIZE;
	const uint32_t	width = map->width * TILE_SIZE;
	t_vector2dint	map_intersect;

	while (!point_out_of_bounds(&ray->direction, height, width))
	{
		map_intersect.x = ray->direction.x / TILE_SIZE - 0.1f;
		map_intersect.y = ray->direction.y / TILE_SIZE;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			break ;
		}
		ray->direction.x -= x_step;
		ray->direction.y += y_step;
	}
}

static void loop_collision_left(t_ray_collision *collision, t_map *map, \
			float y_step, float x_step)
{
	const uint32_t	height = map->height * TILE_SIZE;
	const uint32_t	width = map->width * TILE_SIZE;
	t_vector2dint	map_intersect;

	while (!point_out_of_bounds(&collision->point, height, width))
	{
		map_intersect.x = collision->point.x / TILE_SIZE - 0.1f;
		map_intersect.y = collision->point.y / TILE_SIZE;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			break ;
		}
		collision->point.x -= x_step;
		collision->point.y += y_step;
	}
}

static void	cast_ray_left(t_ray *ray, t_player *player, t_map *map, 
			mlx_image_t *minimap)
{
	const float closest_x = player->x - ((int)player->x % TILE_SIZE);
	const float delta_x = player->x - closest_x;
	float		y_step;

	ray->position.x = player->x;
	ray->position.y = player->y;
	ray->direction = ray->position;
	y_step = -1 * tan(player->dir_angle);
	if (y_step == -INFINITY)
	{
		return ;
	}
	ray->direction.x -= delta_x;
	ray->direction.y += (y_step * delta_x);
	if (y_step == -INFINITY)
	{
		return ;
	}
	get_ray_hit_left(ray, map, y_step * TILE_SIZE, TILE_SIZE);
	draw_line((t_vector2dint){ray->position.x, ray->position.y}, 
	(t_vector2dint){ray->direction.x, ray->direction.y}, 
	minimap, get_rgba(0xe6e6fa, 255));
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
	loop_collision_left(&collision, map, y_step * TILE_SIZE, TILE_SIZE);
	return (collision);
}

t_ray_collision	get_ray_collision_vertical(t_ray *ray, t_map *map)
{
	t_ray_collision	collision;

	if (ray->angle < (M_PI / 2) || ray->angle > ((3 * M_PI) / 2))
	{
		collision = get_ray_collision_right(ray, map);
	}
	if (ray->angle > (M_PI / 2) && ray->angle < ((3 * M_PI) / 2))
	{
		collision = get_ray_collision_left(ray, map);
	}
	ray->direction = collision.point;
	set_ray_distance(ray, &collision);
	return (collision);
}

void	cast_ray_vertical(t_ray *ray, t_player *player, t_map *map, 
		mlx_image_t *minimap)
{
	if (player->dir_angle < (M_PI / 2) || player->dir_angle > ((3 * M_PI) / 2))
	{
		cast_ray_right(ray, player, map, minimap);
	}
	if (player->dir_angle > (M_PI / 2) && player->dir_angle < ((3 * M_PI) / 2))
	{
		cast_ray_left(ray, player, map, minimap);
	}
}
