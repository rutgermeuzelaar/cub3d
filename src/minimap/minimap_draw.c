/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_draw.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 22:09:28 by rmeuzela      #+#    #+#                 */
/*   Updated: 2024/12/27 20:54:51 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "minimap.h"
#include "map.h"
#include "drawing.h"
#include <math.h>

void	draw_rectangle(mlx_image_t *image, t_dimensions dimensions, \
		t_index2d start, const int color)
{
	const uint32_t	x_border = start.x + dimensions.width;
	const uint32_t	y_border = start.y + dimensions.height;

	while (start.y < y_border)
	{
		while (start.x < x_border)
		{
			mlx_put_pixel(image, start.x, start.y, color);
			start.x++;
		}
		start.x -= dimensions.width;
		start.y++;
	}
}

static void set_fill(char texture, t_index2d index2d, mlx_image_t *image)
{
	int				color;
	t_dimensions	dimensions;

	if (texture == '1')
	{
		color = WALL_COLOR;
	}
	if (texture == '0')
	{
		color = FLOOR_COLOR;
	}
	dimensions.height = TILE_SIZE;
	dimensions.width = TILE_SIZE;
	if (index2d.x == 0)
	{
		index2d.x++;
		dimensions.width -= 2;
	}
	else
	{
		dimensions.width--;
	}
	if (index2d.y == 0)
	{
		index2d.y++;
		dimensions.height -= 2;
	}
	else
	{
		dimensions.height--;
	}
	draw_rectangle(image, dimensions, index2d, color);
}

void	draw_minimap(t_map *const map, mlx_image_t *image)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			set_fill(map->map[y][x], (t_index2d){x * TILE_SIZE, y * TILE_SIZE}, image);
			x++;
		}
		y++;
	}
}
