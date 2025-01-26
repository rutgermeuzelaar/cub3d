/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   castv2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 17:41:21 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/26 18:01:12 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include <float.h>
#include <stdio.h>
#include "raycasting.h"
#include "libft.h"
#include "minimap.h"

t_vector2d	get_delta_distance(const float tan_value)
{
	t_vector2d	deltas;

	deltas.x = sqrt(pow(tan_value * 1, 2) + 1);
	deltas.y = sqrt(1 + pow(1 / tan_value, 2));
	return (deltas);
}

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

t_ray_collision	castv2_beast(t_ray *ray, t_map *map, mlx_image_t *minimap)
{
	const float			tan_value = tan(ray->angle);
	const t_vector2d	delta_distance = get_delta_distance(tan_value);
	t_vector2d			total_distance;
	t_vector2dint		map_intersect;
	t_vector2dint		step;
	t_vector2d			offset_start;
	t_vector2d			steps_taken;
	t_ray_collision		collision;
	bool				hit;

	printf("angle: %f\n", ray->angle);
	steps_taken.x = 0;
	steps_taken.y = 0;
	hit = false;
	map_intersect.x = (int)ray->position.x;
	map_intersect.y = (int)ray->position.y;
	if (ray->angle <= FLT_EPSILON || almost_equal(ray->angle, M_PI))
	{
		return ((t_ray_collision){false, ray->position, 0, 0});
	}
	if (ray->angle < M_PI_2 || ray->angle > ((3 * M_PI_2)))
	{
		step.x = 1;
		offset_start.x = (map_intersect.x + 1.0 - ray->position.x);
		total_distance.x = offset_start.x * \
		delta_distance.x;
	}
	else
	{
		step.x = -1;
		offset_start.x = ray->position.x - map_intersect.x;
		total_distance.x = offset_start.x * delta_distance.x;
	}
	if (ray->angle < M_PI)
	{
		step.y = 1;
		offset_start.y = map_intersect.y + 1.0 - ray->position.y;
		total_distance.y = offset_start.y * delta_distance.y;
	}
	else
	{
		step.y = -1;
		offset_start.y = (ray->position.y - map_intersect.y);
		total_distance.y = offset_start.y * delta_distance.y;
	}
	bool	y_last;
	bool	x_last;

	y_last = false;
	x_last = false;
	(void)y_last;
	(void)x_last;
	int	x_pre = 0;
	int y_pre = 0;
	t_vector2dint	prev_map;

	while (!hit)
	{
		x_pre = steps_taken.x;
		y_pre = steps_taken.y;
		prev_map = map_intersect;
		if (total_distance.x < total_distance.y)
		{
			total_distance.x += delta_distance.x;
			map_intersect.x += step.x;
			steps_taken.x += 1.0;
		}
		else
		{
			total_distance.y += delta_distance.y;
			map_intersect.y += step.y;
			steps_taken.y += 1.0;
		}
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			hit = true;
			if (x_pre != steps_taken.x)
			{
				x_last = true;
			}
			if (y_pre != steps_taken.y)
			{
				y_last = true;
			}
			set_cardinal_direction(prev_map, map_intersect, &collision);
			printf("mapint x: %d y: %d\n", map_intersect.x, map_intersect.y);
			draw_rectangle(minimap, (t_rectangle){map_intersect.x * TILE_SIZE, \
			map_intersect.y * TILE_SIZE, TILE_SIZE, TILE_SIZE}, YELLOW);
		}
		(void)map;
	}
	collision.point = ray->position;
	float off_x;
	float off_y;
	float new_dist;
	if (x_last)
	{
		steps_taken.x--;
	}
	if (y_last)
	{
		steps_taken.y--;
	}
	if (total_distance.x < total_distance.y)
	{
		collision.distance = total_distance.x;
	}
	else
	{
		collision.distance = total_distance.y;
	}
	off_y = map_intersect.y - ray->position.y;
	if (step.y < 0)
	{
		off_y = map_intersect.y + 1 - ray->position.y;
	}
	off_x = off_y / tan_value;
	new_dist = off_x * delta_distance.x;
	if (x_last)
	{
		off_x = map_intersect.x - ray->position.x;
		if (step.x < 0)
		{
			off_x = map_intersect.x + 1 - ray->position.x;
		}
		off_y = off_x * tan_value;
		new_dist = off_y * delta_distance.y;
	}
	collision.point.x += off_x;
	collision.point.y += off_y;
	if (new_dist < 0)
	{
		new_dist *= -1;
	}
	collision.distance = new_dist;
	draw_line((t_vector2dint){ray->position.x * TILE_SIZE, ray->position.y * TILE_SIZE}, 
	(t_vector2dint){collision.point.x * TILE_SIZE, collision.point.y * TILE_SIZE}, minimap, GOLD);
	return (collision);
}

