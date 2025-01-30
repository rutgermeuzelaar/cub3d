/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_utilities.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:45:51 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/30 14:34:43 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#define ROUNDING_ERROR 0.1f
#define FLT_EPSILON 1.19209290e-7F
#include <math.h>
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "player.h"
#include "map.h"
#include "shapes.h"
#include "raycasting.h"

t_vector2d	get_delta_distance(const float tan_value)
{
	t_vector2d	deltas;

	deltas.x = sqrt(pow(tan_value * 1, 2) + 1);
	deltas.y = sqrt(1 + pow(1 / tan_value, 2));
	return (deltas);
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
