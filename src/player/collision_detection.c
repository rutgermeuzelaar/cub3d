/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision_detection.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 13:22:17 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/16 14:05:59 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>
#include "player.h"
#include "map.h"
#include "shapes.h"
#include "minimap.h"

int		to_map_intersection(float screen_coordinate)
{
	if (screen_coordinate < TILE_SIZE)
	{
		return (0);
	}
	return (round(screen_coordinate / TILE_SIZE));
}

#include <stdio.h>
bool	is_colliding(t_vector2d point, t_map *map)
{
	t_vector2dint	map_intersect;

	map_intersect.x = to_map_intersection(point.x);
	map_intersect.y = to_map_intersection(point.y);
	printf("col x: %d col y: %d\n", map_intersect.x, map_intersect.y);	
	if (map_intersect.x < 0 || map_intersect.x > (int)map->width - 1)
	{
		return (true);
	}
	if (map_intersect.y < 0 || map_intersect.y > (int)map->height - 1)
	{
		return (true);
	}
	return (map->map[map_intersect.y][map_intersect.x] == '1');
}
 