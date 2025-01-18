/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:46:01 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/18 20:19:40 by rmeuzela      ########   odam.nl         */
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

bool	almost_equal(float a, float b)
{
	return (fabs(fmax(a, b) - fmin(a, b)) <= FLT_EPSILON);
}

void	cast_ray(t_ray *ray, t_player *player, t_map *map, mlx_image_t *minimap)
{
	if (!almost_equal(player->dir_angle, M_PI) && \
	!(player->dir_angle <= FLT_EPSILON) && !almost_equal(player->dir_angle, M_PI * 2))
	{
		cast_ray_horizontal(ray, player, map, minimap);
	}
	if (!(almost_equal(player->dir_angle, (M_PI / 2)) || 
	almost_equal(player->dir_angle, (3 * M_PI) / 2)))
	{
		cast_ray_vertical(ray, player, map, minimap);	
	}
}
