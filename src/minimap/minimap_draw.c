/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_draw.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 22:09:28 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/10 18:24:31 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "libft.h"
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "map.h"
#include "shapes.h"
#include "color.h"

static t_tile	texture_to_tile(const char texture)
{
	if (texture == '0')
	{
		return (TILE_WALK);
	}
	if (texture == '1')
	{
		return (TILE_WALL);
	}
	if (texture == '@' || texture == ' ')
	{
		return (TILE_EMPTY);
	}
	if (ft_strchr("NESW", texture))
	{
		return (TILE_SPAWN);
	}
	assert(false);
	return (TILE_NONE);
}

uint32_t	get_tile_color(t_tile tile)
{
	const uint32_t	colors[TILE_COUNT] = {
	[TILE_EMPTY] = get_rgba(0xe9ecef, 255),
	[TILE_WALK] = GRAY,
	[TILE_WALL] = BLACK,
	[TILE_SPAWN] = PINK
	};

	if (tile == TILE_NONE || tile == TILE_COUNT)
	{
		return (-1);
	}
	return (colors[tile]);
}

static void	set_fill(char texture, t_vector2dint index2d, mlx_image_t *image)
{
	const uint32_t	color = get_tile_color(texture_to_tile(texture));
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
		while (x < ft_strlen(map->map[y]))
		{
			set_fill(map->map[y][x], \
			(t_vector2dint){x * TILE_SIZE, y * TILE_SIZE}, minimap);
			x++;
		}
		y++;
	}
}
