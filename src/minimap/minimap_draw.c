/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_draw.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 22:09:28 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/01 21:31:49 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "minimap.h"
#include "map.h"
#include "shapes.h"
#include <math.h>

static void set_fill(char texture, t_vector2dint index2d, mlx_image_t *image)
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
	draw_rectangle(image, \
	(t_rectangle){index2d.x, index2d.y, dimensions.width, dimensions.height}, \
	color);
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
			set_fill(map->map[y][x], (t_vector2dint){x * TILE_SIZE, y * TILE_SIZE}, image);
			x++;
		}
		y++;
	}
}
