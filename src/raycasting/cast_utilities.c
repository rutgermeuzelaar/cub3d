/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_utilities.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:45:51 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/21 17:30:46 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#define ROUNDING_ERROR 0.1f
#include <math.h>
#include <stdio.h>
#include <float.h>
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "player.h"
#include "map.h"
#include "shapes.h"
#include "raycasting.h"

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

int		floor_multiple(float number, int multiple)
{
	return (multiple * floor(number / multiple));
}

int		ceil_multiple(float number, int multiple)
{
	return (multiple * ceil(number / multiple));
}

void	set_ray_distance(t_ray *ray, t_ray_collision *collision)
{
	float	delta_x;
	float	delta_y;

	delta_x = ray->position.x - collision->point.x;
	delta_y = ray->position.y - collision->point.y;
	if (delta_x < 0)
	{
		delta_x *= -1.0f;
	}
	if (delta_y < 0)
	{	
		delta_y *= -1.0f;
	}
	collision->distance = sqrt(pow(delta_y, 2) + pow(delta_x, 2));
}

bool	almost_equal(float a, float b)
{
	return (fabs(fmax(a, b) - fmin(a, b)) <= FLT_EPSILON);
}

void	set_ray_angles(t_ray *rays, t_player *player)
{
	const float	fov = 66 * RADIAN;
	const float	offset = fov / player->ray_count;
	float		start;
	int			i;

	i = 0;
	start = player->dir_angle + (fov / 2);
	while (i < player->ray_count)
	{
		rays[i].angle = start - (offset * i);
		if (rays[i].angle <= 0)
		{
			rays[i].angle += (M_PI * 2);
		}
		if (rays[i].angle >= (M_PI * 2))
		{
			rays[i].angle -= (M_PI * 2);
		}
		i++;
	}
}

void	progress_collision(t_ray_collision *collision, t_map *map, \
		t_cardinal_direction cardinal, t_vector2d step)
{
	const uint32_t	height = map->height * TILE_SIZE;
	const uint32_t	width = map->width * TILE_SIZE;
	t_vector2dint	map_intersect;

	(void)cardinal;
	while (!point_out_of_bounds(&collision->point, height, width))
	{
		map_intersect.x = collision->point.x / TILE_SIZE;
		map_intersect.y = collision->point.y / TILE_SIZE;
		if (map->map[map_intersect.y][map_intersect.x] == '1')
		{
			break ;
		}
		collision->point.x += step.x;
		collision->point.y += step.y;
	}
}
