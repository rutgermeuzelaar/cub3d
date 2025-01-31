/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_helper.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 14:04:09 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/31 19:01:45 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "color.h"
#include "map.h"
#include "raycasting_structs.h"
#include "shapes.h"
#include "raycasting.h"
#include "minimap.h"

static void	set_cardinal_direction(t_vector2dint point_1, \
			t_vector2dint point_2, t_ray_collision *collision)
{
	const int	delta_x = point_2.x - point_1.x;
	const int	delta_y = point_2.y - point_1.y;

	if (delta_y == -1)
	{
		collision->cardinal = NORTH;
	}
	if (delta_y == 1)
	{
		collision->cardinal = SOUTH;
	}
	if (delta_x == -1)
	{
		collision->cardinal = WEST;
	}
	if (delta_x == 1)
	{
		collision->cardinal = EAST;
	}
}

static void	set_direction(t_cast_xl *cast_xl)
{
	if (cast_xl->total_distance.x < cast_xl->total_distance.y)
	{
		cast_xl->total_distance.x += cast_xl->delta_distance.x;
		cast_xl->map_intersect.x += cast_xl->step.x;
	}
	else
	{
		cast_xl->total_distance.y += cast_xl->delta_distance.y;
		cast_xl->map_intersect.y += cast_xl->step.y;
	}
}

static void	set_intersection(t_cast_xl *cast_xl, mlx_image_t *minimap, \
			t_map *map)
{
	t_vector2dint	prev_map;

	while (true)
	{
		prev_map = cast_xl->map_intersect;
		set_direction(cast_xl);
		if (map->map[cast_xl->map_intersect.y][cast_xl->map_intersect.x] == '1')
		{
			if (prev_map.x != cast_xl->map_intersect.x)
			{
				cast_xl->x_last = true;
			}
			set_cardinal_direction(prev_map, cast_xl->map_intersect, \
			&cast_xl->collision);
			draw_rectangle(minimap, (t_rectangle){cast_xl->map_intersect.x * \
			TILE_SIZE, cast_xl->map_intersect.y * TILE_SIZE, TILE_SIZE, \
			TILE_SIZE}, YELLOW);
			break ;
		}
	}
}

static void	set_ray_collision(t_ray *ray, t_cast_xl *cast_xl)
{
	float	off_x;
	float	off_y;
	float	new_dist;

	cast_xl->collision.point = ray->position;
	off_y = cast_xl->map_intersect.y - ray->position.y;
	if (cast_xl->step.y < 0)
		off_y = cast_xl->map_intersect.y + 1 - ray->position.y;
	off_x = off_y / cast_xl->tan_value;
	new_dist = off_x * cast_xl->delta_distance.x;
	if (cast_xl->x_last)
	{
		off_x = cast_xl->map_intersect.x - ray->position.x;
		if (cast_xl->step.x < 0)
			off_x = cast_xl->map_intersect.x + 1 - ray->position.x;
		off_y = off_x * cast_xl->tan_value;
		new_dist = off_y * cast_xl->delta_distance.y;
	}
	cast_xl->collision.point.x += off_x;
	cast_xl->collision.point.y += off_y;
	if (new_dist < 0)
		new_dist *= -1;
	cast_xl->collision.distance = new_dist;
}

void	cast_ray_helper(t_cast_xl *cast_xl, t_map *map, mlx_image_t *minimap, \
		t_ray *ray)
{
	set_intersection(cast_xl, minimap, map);
	set_ray_collision(ray, cast_xl);
}
