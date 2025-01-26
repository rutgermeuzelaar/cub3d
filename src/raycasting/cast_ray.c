/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:46:01 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/26 16:05:34 by rmeuzela      ########   odam.nl         */
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

void	draw_ray_stripe(t_player *player, t_ray *ray, mlx_image_t *image, 
			t_ray_collision collision, int ray_index)
{
	const float ray_thickness = round(WINDOW_WIDTH / player->ray_count);
	t_rectangle	stripe;
	float		distance;

	distance = fix_fisheye(player->dir_angle, ray->angle, collision.distance);
	stripe.height = (WINDOW_HEIGHT * TILE_SIZE) / (distance * TILE_SIZE);
	if (stripe.height > WINDOW_HEIGHT)
	{
		stripe.height = WINDOW_HEIGHT;
	}
	stripe.width = ray_thickness;
	stripe.x = ray_thickness * ray_index;
	stripe.y = (WINDOW_HEIGHT / 2) - stripe.height / 2;
	// printf("STRIPE: x: %f y: %f width: %d height: %d\n",stripe.x, stripe.y, stripe.width, stripe.height);
	if (collision.cardinal == NORTH || collision.cardinal == SOUTH)
	{
		t_color cheese;

		cheese.rgba = RED;
		cheese.bytes.red -= 75;
		draw_rectangle(image, stripe, cheese.rgba);
	}
	else
	{
		draw_rectangle(image, stripe, RED);
	}
}

void	cast_ray_all(t_ray *rays, t_player *player, t_map *map, \
		mlx_image_t *minimap, mlx_image_t *screen)
{
	int				i;
	t_ray_collision	collision;

	(void)screen;
	(void)collision;
	(void)minimap;
	i = player->ray_count - 1;
	while (i >= 0)
	{
		// printf("rays[i] angle: %f\n", rays[i].angle);
		// collision = cast_ray(&rays[i], player, map, minimap);
		rays[i].position.x = player->x;
		rays[i].position.y = player->y;
		// rays[i].angle = player->dir_angle;
		collision = castv2_beast(&rays[i], map, minimap);
		// printf("i: %d dist: %f\n", i, collision.distance);
		// printf("collision")
		draw_ray_stripe(player, &rays[i], screen, collision, i);
		i--;
	}
}
