/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:46:01 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/20 20:09:39 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include <stdio.h>
#include <float.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "player.h"
#include "map.h"
#include "minimap.h"
#include "raycasting.h"
#include "cub3d.h"

t_ray_collision	get_ray_collision(t_ray *ray, t_map *map)
{
	t_ray_collision	collision_horizontal;
	t_ray_collision	collision_vertical;

	if (ray->angle <= FLT_EPSILON || almost_equal(ray->angle, M_PI))
	{
		return ((t_ray_collision){false, ray->position, 0, 0});
	}
	if (!almost_equal(ray->angle, M_PI) && \
	!(ray->angle <= FLT_EPSILON) && !almost_equal(ray->angle, M_PI * 2))
	{
		collision_horizontal = get_ray_collision_horizontal(ray, map);
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

float	cast_ray(t_ray *ray, t_player *player, t_map *map, mlx_image_t *minimap)
{
	t_ray_collision	collision;

	ray->position.x = player->x * TILE_SIZE;
	ray->position.y = player->y * TILE_SIZE;
	collision = get_ray_collision(ray, map);
	ray->direction = collision.point;
	draw_line((t_vector2dint){ray->position.x, ray->position.y}, 
	(t_vector2dint){ray->direction.x, ray->direction.y}, 
	minimap, player->ray_color.rgba);
	return (collision.distance);
}

static float fix_fisheye(float player_angle, float ray_angle, float distance)
{
	float	angle_delta;
	
	angle_delta = player_angle - ray_angle;
	if (angle_delta < 0)
	{
		angle_delta += 2 * M_PI;
	}
	if (angle_delta > (M_PI * 2))
	{
		angle_delta -= M_PI * 2;
	}
	return (cos(angle_delta) * distance);
}

static void	draw_ray_stripe(t_player *player, t_ray *ray, mlx_image_t *image, float distance, \
			int ray_total, int ray_index, t_map *map)
{
	const float ray_thickness = WINDOW_WIDTH / ray_total;
	// const float base_height = WINDOW_HEIGHT / 2;
	t_rectangle	stripe;

	(void)ray;
	printf("distance: %f\n", distance);
	(void)map;
	distance = fix_fisheye(player->dir_angle, ray->angle, distance);
	stripe.height = (WINDOW_HEIGHT * TILE_SIZE) / distance;
	if (stripe.height > WINDOW_HEIGHT)
	{
		stripe.height = WINDOW_HEIGHT;
	}
	stripe.width = ray_thickness;
	stripe.x = ray_thickness * ray_index;
	stripe.y = (WINDOW_HEIGHT / 2) - stripe.height / 2;
	draw_rectangle(image, stripe, RED);
}

void	cast_ray_all(t_ray *rays, t_player *player, t_map *map, \
		mlx_image_t *minimap, mlx_image_t *screen)
{
	int		i;
	float	distance;
	i = 0;
	while (i < player->ray_count)
	{
		printf("rays[i] angle: %f\n", rays[i].angle);
		distance = cast_ray(&rays[i], player, map, minimap);
		draw_ray_stripe(player, &rays[i], screen, distance, player->ray_count, i, map);
		i++;
	}
}
