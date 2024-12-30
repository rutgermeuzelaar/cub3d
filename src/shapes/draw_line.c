/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/30 22:10:23 by rmeuzela      #+#    #+#                 */
/*   Updated: 2024/12/30 22:57:56 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "MLX42/MLX42.h"
#include "shapes.h"

void	draw_line(int x1, int y1, int x2, int y2, mlx_image_t *image, \
		uint32_t color)
{
	const int	delta_x = x2 - x1;
	const int	delta_y = y2 - y1;
	double		x_incr;
	double		y_incr;
	int			steps;
	int			i;
	double		x_current;
	double		y_current;

	i = 0;
	x_current = x1;
	y_current = y1;
	steps = delta_x;
	if (delta_y > delta_x)
	{
		steps = delta_y;
	}
	x_incr = (float)delta_x / steps;
	y_incr = (float)delta_y / steps;
	while (i < steps)
	{
		mlx_put_pixel(image, round(x_current), round(y_current), color);
		x_current += x_incr;
		y_current += y_incr;	
		i++;
	}
}
