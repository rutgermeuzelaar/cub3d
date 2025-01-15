/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/30 22:10:23 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/15 18:48:10 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "shapes.h"

// Bresenham's algorithm
void	draw_line(t_vector2dint point_1, t_vector2dint point_2, \
		mlx_image_t *image, uint32_t color)
{
	int	delta_x;
	int	delta_y;
	
	delta_x = point_2.x - point_1.x;
	delta_y = point_2.y - point_1.y;
	if (delta_x < 0)
	{
		delta_x *= -1;
	}
	if (delta_y < 0)
	{
		delta_y *= -1;
	}
	if (delta_x > delta_y)
	{
		draw_line_horizontal(point_1, point_2, image, color);
	}
	else
	{
		draw_line_vertical(point_1, point_2, image, color);
	}
}
