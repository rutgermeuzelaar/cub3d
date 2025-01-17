/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_utilities.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:45:51 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/17 18:08:10 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "player.h"
#include "map.h"
#include "shapes.h"

// the ray direction gets out of bounds
bool	point_out_of_bounds(t_vector2d *point, const uint32_t height, \
		const uint32_t width)
{
	bool	out_of_bounds;

	out_of_bounds = false;
	if (point->x < 0)
	{
		out_of_bounds = true;
		point->x = 0;
	}
	if (point->x > width)
	{
		out_of_bounds = true;
		point->x = width;
	}
	if (point->y < 0)
	{
		out_of_bounds = true;
		point->y = 0;
	}
	if (point->y > height)
	{
		out_of_bounds = true;
		point->y = height;
	}
	return (out_of_bounds);
}

// static void	round_intersection(t_ray *ray, float y_step, float x_step)
// {
// 	// ray down
// 	if (y_step > 0)
// 	{
		
// 	}
// 	if ()
// }
// void set_ray_hit(t_ray *ray, t_map *map, float y_step, float x_step)
// {
// 	const uint32_t	height = map->height * TILE_SIZE;
// 	const uint32_t	width = map->width * TILE_SIZE;
// 	t_vector2dint	map_intersect;

// 	while (!point_out_of_bounds(&ray->direction, height, width))
// 	{
// 		map_intersect.x = ray->direction.x / TILE_SIZE;
// 		map_intersect.y = ray->direction.y / TILE_SIZE;
// 		if (map->map[map_intersect.y][map_intersect.x] == '1')
// 		{
// 			break ;
// 		}
// 		ray->direction.x -= x_step;
// 		ray->direction.y -= y_step;
// 	}
// }

