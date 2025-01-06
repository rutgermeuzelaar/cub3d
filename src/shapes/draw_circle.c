/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_circle.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/06 19:57:01 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/06 20:09:36 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "MLX42/MLX42.h"
#include "shapes.h"

void	draw_circle_line(mlx_image_t *image, t_vector2d center, float radius, \
		int32_t color)
{
	float	angle;
	int		x;
	int		y;

	angle = 0;
	while (angle < (M_PI * 2))
	{
		x = center.x + (cos(angle) * radius);
		y = center.y + (sin(angle) * radius);
		mlx_put_pixel(image, x, y, color);
		angle += 0.1;
	}
}
