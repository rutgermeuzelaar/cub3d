/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   castv2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 17:41:21 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/22 22:06:05 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include <float.h>
#include <stdio.h>
#include "raycasting.h"
#include "libft.h"

t_vector2d	get_delta_distance(float angle)
{
	const float tan_value = tan(angle);
	t_vector2d	deltas;

	deltas.y = sqrt(pow(tan_value * 1, 2) + 1);
	deltas.x = sqrt(1 + pow(1 / tan_value, 2));
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

t_ray_collision	castv2_beast(t_ray *ray, t_map *map)
{
	const t_vector2d	delta_distance = get_delta_distance(ray->angle);
	t_vector2d			total_distance;
	t_vector2dint		map_intersect;
	t_vector2dint		step;
	t_ray_collision		collision;
	bool				hit;

	printf("BEAST ENTER\n");
	hit = false;
	map_intersect.x = (int)ray->position.x;
	map_intersect.y = (int)ray->position.y;
	printf("map_intersect.x: %d map_intersect.y: %d\n", map_intersect.x, map_intersect.y);
	printf("ray x: %f y: %f\n", ray->position.x, ray->position.y);
	if (ray->angle < M_PI_2 || ray->angle > ((3 * M_PI_2)))
	{
		step.x = 1;
		printf("CHEEK: %f\n", (map_intersect.x + 1.0 - ray->position.x));
		total_distance.y = (map_intersect.x + 1.0 - ray->position.x) * \
		delta_distance.x;
	}
	else
	{
		step.x = -1;
		total_distance.y = (ray->position.x - map_intersect.x) * delta_distance.x;
	}
	if (ray->angle < M_PI)
	{
		step.y = 1;
		total_distance.x = (map_intersect.y + 1.0 - ray->position.y) * delta_distance.y;
	}
	else
	{
		step.y = -1;
		total_distance.x = (ray->position.y - map_intersect.y) * delta_distance.y;
	}
	printf("total_distance x: %f y: %f\n", total_distance.x, total_distance.y);
	printf("step.x: %d step.y: %d\n",step.x, step.y);
	int i;

	i = 0;
	while (!hit)
	{
		if (total_distance.x < total_distance.y)
		{
			total_distance.x += delta_distance.x;
			map_intersect.x += step.x;
	
		}
		else
		{
			total_distance.y += delta_distance.y;
			map_intersect.y += step.y;
		}
		i++;
		printf("map_intersect.y: %d map_intersect.x: %d\n", map_intersect.y, map_intersect.x);
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			hit = true;
		}
		(void)map;
		if (i > 2)
		{
			hit = true;
		}
	}
	printf("distance x: %f distance y: %f\n", total_distance.x, total_distance.y);
	ft_memset(&collision, 0, sizeof(t_ray_collision));
	printf("BEAST EXIT\n\n");
	return (collision);
}
