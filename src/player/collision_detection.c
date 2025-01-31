/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision_detection.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 13:22:17 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/31 18:57:17 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include <stdbool.h>
#include "player.h"
#include "map.h"
#include "shapes.h"
#include "raycasting.h"

bool	collide_circle(const t_vector2d position, t_map *map, \
		const float radius)
{
	float			i;
	t_vector2d		circle_point;
	t_vector2dint	map_intersection;

	i = 0;
	circle_point.x = 0;
	circle_point.y = 0;
	(void)map;
	while (i < (M_PI * 2))
	{
		circle_point.x = cos(i) * radius;
		circle_point.y = sin(i) * radius;
		map_intersection.x = (int)(position.x + circle_point.x);
		map_intersection.y = (int)(position.y + circle_point.y);
		if (map->map[map_intersection.y][map_intersection.x] == '1')
		{
			return (true);
		}
		i += RADIAN;
	}
	return (false);
}
