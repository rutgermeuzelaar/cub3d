/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   castv2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 17:41:21 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/24 19:58:53 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include <float.h>
#include <stdio.h>
#include "raycasting.h"
#include "libft.h"
#include "minimap.h"

t_vector2d	get_delta_distance(float angle)
{
	const float tan_value = tan(angle);
	t_vector2d	deltas;

	deltas.x = sqrt(pow(tan_value * 1, 2) + 1);
	deltas.y = sqrt(1 + pow(1 / tan_value, 2));
	printf("deltas.y: %f, deltas.x: %f, angle: %f\n", deltas.y, deltas.x, angle);
	return (deltas);
	// if (!almost_equal(angle, M_PI) && 
	// !(angle <= FLT_EPSILON) && !almost_equal(angle, M_PI * 2))
	// {
	// 	// horizontal
	// 	collision_horizontal = get_ray_collision_horizontal(ray, map);
	// }
	// if (!(almost_equal(ray->angle, (M_PI / 2)) || 
	// almost_equal(ray->angle, (3 * M_PI) / 2)))
	
}

t_ray_collision	castv2_beast(t_ray *ray, t_map *map, mlx_image_t *minimap)
{
	const t_vector2d	delta_distance = get_delta_distance(ray->angle);
	t_vector2d			total_distance;
	t_vector2dint		map_intersect;
	t_vector2dint		step;
	t_vector2d			offset_start;
	t_vector2dint		steps_taken;
	t_ray_collision		collision;
	bool				hit;

	printf("BEAST ENTER\n");
	steps_taken.x = 0;
	steps_taken.y = 0;
	hit = false;
	map_intersect.x = (int)ray->position.x;
	map_intersect.y = (int)ray->position.y;
	printf("START: map_intersect.x: %d map_intersect.y: %d\n", map_intersect.x, map_intersect.y);
	printf("ray x: %f y: %f\n", ray->position.x, ray->position.y);
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
	printf("OFFSET x: %f y: %f\n", offset_start.x, offset_start.y);
	printf("total_distance x: %f y: %f\n", total_distance.x, total_distance.y);
	printf("step.x: %d step.y: %d\n",step.x, step.y);
	bool	y_last;
	bool	x_last;

	y_last = false;
	x_last = true;
	(void)y_last;
	(void)x_last;
	int	x_pre = 0;
	int y_pre = 0;
	while (!hit)
	{
		x_pre = steps_taken.x;
		y_pre = steps_taken.y;
		if (total_distance.x < total_distance.y)
		{
			total_distance.x += delta_distance.x;
			map_intersect.x += step.x;
			steps_taken.x++;
		}
		else
		{
			total_distance.y += delta_distance.y;
			map_intersect.y += step.y;
			steps_taken.y++;
		}
		printf("map_intersect.y: %d map_intersect.x: %d\n", map_intersect.y, map_intersect.x);
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
			draw_rectangle(minimap, (t_rectangle){map_intersect.x * TILE_SIZE, \
			map_intersect.y * TILE_SIZE, TILE_SIZE, TILE_SIZE}, YELLOW);
		}
		(void)map;
	}
	printf("steps taken x: %d y: %d\n", steps_taken.x, steps_taken.y);
	collision.point = ray->position;
	if (total_distance.x < total_distance.y)
	{
		collision.distance = total_distance.x;
		if (y_last)
		{
			collision.distance -= delta_distance.x;
		}
	}
	else
	{
		collision.distance = total_distance.y - delta_distance.y;
		if (x_last)
		{
			collision.distance -= delta_distance.y;
		}
	}
	collision.point.x += collision.distance * cos(ray->angle);
	collision.point.y += collision.distance * sin(ray->angle);

	printf("SHADY x: %f y: %f\n", collision.point.x, collision.point.y);
	draw_line((t_vector2dint){ray->position.x * TILE_SIZE, ray->position.y * TILE_SIZE}, 
	(t_vector2dint){collision.point.x * TILE_SIZE, collision.point.y * TILE_SIZE}, minimap, GOLD);
	printf("distance x: %f distance y: %f\n", total_distance.x, total_distance.y);
	printf("BEAST EXIT\n\n");
	return (collision);
}
