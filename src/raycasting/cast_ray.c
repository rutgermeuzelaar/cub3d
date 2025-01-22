/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:46:01 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/22 21:13:14 by rmeuzela      ########   odam.nl         */
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

t_ray_collision	get_ray_collision(t_ray *ray, t_map *map, mlx_image_t *minimap)
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
	(void)minimap;
	// draw_line((t_vector2dint){ray->position.x, ray->position.y}, 
	// (t_vector2dint){collision_horizontal.point.x, collision_horizontal.point.y}, minimap, PINK);
	// draw_line((t_vector2dint){ray->position.x, ray->position.y}, 
	// (t_vector2dint){collision_vertical.point.x, collision_vertical.point.y}, minimap, RED);

	printf("HOR DIST: %f VERT DIST: %f\n", collision_horizontal.distance, collision_vertical.distance);
	if (collision_horizontal.distance > collision_vertical.distance)
	{
		return (collision_vertical);
	}
	return (collision_horizontal);
}

t_ray_collision	cast_ray(t_ray *ray, t_player *player, t_map *map, mlx_image_t *minimap)
{
	t_ray_collision	collision;

	ray->position.x = player->x * TILE_SIZE;
	ray->position.y = player->y * TILE_SIZE;
	collision = get_ray_collision(ray, map, minimap);
	ray->direction = collision.point;
	draw_line((t_vector2dint){ray->position.x, ray->position.y}, 
	(t_vector2dint){ray->direction.x, ray->direction.y}, 
	minimap, player->ray_color.rgba);
	return (collision);
}

// static float fix_fisheye(float player_angle, float ray_angle, float distance)
// {
// 	float	angle_delta;
	
// 	angle_delta = player_angle - ray_angle;
// 	if (angle_delta < 0)
// 	{
// 		angle_delta += 2 * M_PI;
// 	}
// 	if (angle_delta > (M_PI * 2))
// 	{
// 		angle_delta -= M_PI * 2;
// 	}
// 	return (cos(angle_delta) * distance);
// }

// static void	draw_ray_stripe(t_player *player, t_ray *ray, mlx_image_t *image, 
// 			t_ray_collision collision, int ray_index)
// {
// 	const float ray_thickness = WINDOW_WIDTH / player->ray_count;
// 	t_rectangle	stripe;
// 	float		distance;

// 	distance = fix_fisheye(player->dir_angle, ray->angle, collision.distance);
// 	stripe.height = (WINDOW_HEIGHT * TILE_SIZE) / distance;
// 	if (stripe.height > WINDOW_HEIGHT)
// 	{
// 		stripe.height = WINDOW_HEIGHT;
// 	}
// 	stripe.width = ray_thickness;
// 	stripe.x = ray_thickness * ray_index + 40;
// 	printf("ray intel: %f total: %f\n", ray_thickness, ray_thickness * player->ray_count);
// 	stripe.y = (WINDOW_HEIGHT / 2) - stripe.height / 2;
// 	printf("CARDINAL: %d\n", collision.cardinal);
// 	printf("stripe.x: %f\n", stripe.x);
// 	if (collision.cardinal == NORTH || collision.cardinal == SOUTH)
// 	{
// 		t_color cheese;

// 		cheese.rgba = RED;
// 		cheese.bytes.red -= 75;
// 		draw_rectangle(image, stripe, cheese.rgba);
// 	}
// 	else
// 	{
// 		draw_rectangle(image, stripe, RED);
// 	}
// }

void	cast_ray_all(t_ray *rays, t_player *player, t_map *map, \
		mlx_image_t *minimap, mlx_image_t *screen)
{
	int				i;
	t_ray_collision	collision;

	(void)screen;
	(void)collision;
	(void)minimap;
	i = 0;
	while (i < player->ray_count)
	{
		// printf("rays[i] angle: %f\n", rays[i].angle);
		// collision = cast_ray(&rays[i], player, map, minimap);
		rays[i].position.x = player->x;
		rays[i].position.y = player->y;
		rays[i].angle = player->dir_angle;
		collision = castv2_beast(&rays[i], map);
		// printf("collision")
		// draw_ray_stripe(player, &rays[i], screen, collision, i);
		i++;
	}
}
