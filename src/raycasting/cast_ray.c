/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 17:41:21 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/06 22:26:40 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#define FLT_EPSILON 1.19209290e-7F
#include <math.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "color.h"
#include "map.h"
#include "raycasting_structs.h"
#include "shapes.h"
#include "raycasting.h"
#include "libft.h"
#include "minimap.h"

static void	init_cast_vertical(t_ray *ray, t_cast_xl *cast_xl)
{
	if (ray->angle < M_PI)
	{
		cast_xl->step.y = 1;
		cast_xl->total_distance.y = (cast_xl->map_intersect.y + 1.0 - \
		ray->position.y) * cast_xl->delta_distance.y;
	}
	else
	{
		cast_xl->step.y = -1;
		cast_xl->total_distance.y = (ray->position.y - \
		cast_xl->map_intersect.y) * cast_xl->delta_distance.y;
	}
}

static void	init_cast_horizontal(t_ray *ray, t_cast_xl *cast_xl)
{
	if (ray->angle < M_PI_2 || ray->angle > ((3 * M_PI_2)))
	{
		cast_xl->step.x = 1;
		cast_xl->total_distance.x = (cast_xl->map_intersect.x + 1.0 - \
		ray->position.x) * \
		cast_xl->delta_distance.x;
	}
	else
	{
		cast_xl->step.x = -1;
		cast_xl->total_distance.x = (ray->position.x - \
		cast_xl->map_intersect.x) * \
		cast_xl->delta_distance.x;
	}
}

static void	init_cast(t_ray *ray, t_cast_xl	*cast_xl)
{
	ft_memset(cast_xl, 0, sizeof(t_cast_xl));
	cast_xl->tan_value = tan(ray->angle);
	cast_xl->delta_distance = get_delta_distance(cast_xl->tan_value);
	cast_xl->map_intersect.x = (int)ray->position.x;
	cast_xl->map_intersect.y = (int)ray->position.y;
	init_cast_horizontal(ray, cast_xl);
	init_cast_vertical(ray, cast_xl);
}

t_ray_collision	cast_ray(t_ray *ray, t_map *map, mlx_image_t *minimap)
{
	t_cast_xl			cast_xl;
	t_vector2dint		point_1;
	t_vector2dint		point_2;

	init_cast(ray, &cast_xl);
	cast_ray_helper(&cast_xl, map, minimap, ray);
	point_1.x = ray->position.x * TILE_SIZE;
	point_1.y = ray->position.y * TILE_SIZE;
	point_2.x = cast_xl.collision.point.x * TILE_SIZE;
	point_2.y = cast_xl.collision.point.y * TILE_SIZE;
	draw_line(point_1, point_2, minimap, GOLD);
	return (cast_xl.collision);
}
