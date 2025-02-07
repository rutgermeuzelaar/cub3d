/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_draw.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 22:09:28 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/07 20:25:08 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "libft.h"
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "map.h"
#include "shapes.h"
#include "color.h"

static uint32_t	set_fill_helper(const char texture)
{
	if (texture == WALK_TILE)
	{
		return (GRAY);
	}
	if (texture == WALL_TILE)
	{
		return (BLACK);
	}
	if (texture == EMPTY_TILE)
	{
		return (WHITE);
	}
	if (ft_strchr("NESW", texture))
	{
		return (RED);
	}
	return (PINK);
}

static void	set_fill(char texture, t_vector2dint index2d, mlx_image_t *image)
{
	const uint32_t	color = set_fill_helper(texture);
	t_dimensions	dimensions;

	dimensions.height = TILE_SIZE;
	dimensions.width = TILE_SIZE;
	if (index2d.x == 0)
	{
		index2d.x++;
		dimensions.width -= 2;
	}
	else
		dimensions.width--;
	if (index2d.y == 0)
	{
		index2d.y++;
		dimensions.height -= 2;
	}
	else
		dimensions.height--;
	draw_rectangle(image, \
	(t_rectangle){index2d.x, index2d.y, dimensions.width, dimensions.height}, \
	color);
}

void	draw_minimap(t_map *const map, mlx_image_t *minimap)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			set_fill(map->map[y][x], \
			(t_vector2dint){x * TILE_SIZE, y * TILE_SIZE}, minimap);
			x++;
		}
		y++;
	}
}
