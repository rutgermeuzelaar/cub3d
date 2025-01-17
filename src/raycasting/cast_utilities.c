/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:45:51 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/17 15:45:01 by rmeuzela      ########   odam.nl         */
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
bool		point_out_of_bounds(t_vector2d *point, const uint32_t height, \
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
