/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:46:01 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/18 22:56:45 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <float.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "player.h"
#include "map.h"
#include "minimap.h"
#include "raycasting.h"

t_ray_collision	get_ray_collision(t_ray *ray, t_map *map, mlx_image_t *minimap)
{
	t_ray_collision	collision_horizontal;
	t_ray_collision	collision_vertical;

	if (ray->angle <= FLT_EPSILON || almost_equal(ray->angle, M_PI))
	{
		return ((t_ray_collision){false, ray->position, 0});
	}
	if (!almost_equal(ray->angle, M_PI) && \
	!(ray->angle <= FLT_EPSILON) && !almost_equal(ray->angle, M_PI * 2))
	{
		collision_horizontal = get_ray_collision_horizontal(ray, map, minimap);
	}
	if (!(almost_equal(ray->angle, (M_PI / 2)) || 
	almost_equal(ray->angle, (3 * M_PI) / 2)))
	{
		collision_vertical = get_ray_collision_vertical(ray, map);
	}
	if (collision_horizontal.distance > collision_vertical.distance)
	{
		return (collision_vertical);
	}
	return (collision_horizontal);
}

void	cast_ray(t_ray *ray, t_player *player, t_map *map, mlx_image_t *minimap)
{
	t_ray_collision	collision;

	ray->position.x = player->x;
	ray->position.y = player->y;
	ray->angle = player->dir_angle;
	collision = get_ray_collision(ray, map, minimap);
	ray->direction = collision.point;
	draw_line((t_vector2dint){ray->position.x, ray->position.y}, 
	(t_vector2dint){ray->direction.x, ray->direction.y}, 
	minimap, get_rgba(0xe6e6fa, 255));
}
