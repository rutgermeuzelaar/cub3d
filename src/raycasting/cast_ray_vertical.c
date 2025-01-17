/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_vertical.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 22:55:55 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/17 17:46:25 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <assert.h>
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
		map_intersect.x = ray->direction.x / TILE_SIZE - 0.1f;
		map_intersect.y = ray->direction.y / TILE_SIZE;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			break ;
		}
		ray->direction.x += x_step;
		ray->direction.y -= y_step;
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
