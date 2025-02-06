/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_all.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:46:01 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/06 22:35:37 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include <assert.h>
#include "color.h"
#include "raycasting_structs.h"
#include "shapes.h"
#include "player.h"
#include "minimap.h"
#include "raycasting.h"
#include "cub3d.h"
#include "textures.h"

static void	draw_ray_stripe(t_game *game, t_ray *ray, \
			t_ray_collision collision, const int ray_index)
{
	const float				ray_thickness = round(WINDOW_WIDTH / \
							game->player.ray_count);
	const float				distance = cos(game->player.dir_angle - \
							ray->angle) * collision.distance;
	t_textured_rectangle	stripe;

	assert(distance > 0);
	stripe.texture_y = 0;
	stripe.height = (WINDOW_HEIGHT * TILE_SIZE) / (distance * TILE_SIZE);
	stripe.scale_distance = stripe.height;
	if (stripe.height > WINDOW_HEIGHT)
	{
		stripe.texture_y = (stripe.height - WINDOW_HEIGHT) / 2;
		stripe.height = WINDOW_HEIGHT;
	}
	stripe.width = ray_thickness;
	stripe.x = ray_thickness * (game->player.ray_count - ray_index - 1);
	stripe.y = (WINDOW_HEIGHT / 2) - stripe.height / 2;
	draw_textured_rectangle(game, stripe, collision);
}

void	cast_ray_all(t_game *game)
{
	int				i;
	t_ray_collision	collision;

	i = 0;
	while (i < game->player.ray_count)
	{
		game->player.rays[i].position.x = game->player.x;
		game->player.rays[i].position.y = game->player.y;
		collision = cast_ray(&game->player.rays[i], &game->map, game->minimap);
		draw_ray_stripe(game, &game->player.rays[i], collision, i);
		i++;
	}
}
