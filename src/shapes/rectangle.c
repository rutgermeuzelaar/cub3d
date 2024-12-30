/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rectangle.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/30 21:28:57 by rmeuzela      #+#    #+#                 */
/*   Updated: 2024/12/30 21:35:17 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "shapes.h"

void	draw_rectangle(mlx_image_t *image, t_rectangle rectangle, \
		uint32_t color)
{
	const uint32_t	x_border = rectangle.x + rectangle.width;
	const uint32_t	y_border = rectangle.y + rectangle.height;

	while (rectangle.y < y_border)
	{
		while (rectangle.x < x_border)
		{
			mlx_put_pixel(image, rectangle.x, rectangle.y, color);
			rectangle.x++;
		}
		rectangle.x -= rectangle.width;
		rectangle.y++;
	}
}
