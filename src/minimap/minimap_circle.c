/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_circle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 17:52:47 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/04 17:59:04 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "map.h"
#include "shapes.h"
#include "color.h"

// everything should move per pixel to make it easier
static uint32_t	copy_next_pixel(mlx_image_t *source, t_rectangle copy_slice, \
				t_vector2dint *point)
{
	t_color		color;
	int			i;

	i = 0;
	color.rgba = PINK;
	if (point->y == (int32_t)copy_slice.height)
		return (color.rgba);
	if (point->x < (int32_t)copy_slice.width)
	{
		i = ((int)copy_slice.x + point->x + (((int)copy_slice.y + point->y) * \
		source->width)) * 4;
		color.bytes.red = source->pixels[i];
		color.bytes.green = source->pixels[i + 1];
		color.bytes.blue = source->pixels[i + 2];
		color.bytes.alpha = source->pixels[i + 3];
		point->x++;
	}
	else
	{
		point->x = 0;
		point->y++;
		return (copy_next_pixel(source, copy_slice, point));
	}
	return (color.rgba);
}

static bool	inside_circle(t_vector2dint point, t_vector2dint circle_center, \
			const float radius)
{
	return ((pow(point.x - circle_center.x, 2) + \
	pow(point.y - circle_center.y, 2)) < pow(radius, 2));
}

static void	draw_slice_circle(mlx_image_t *dest, mlx_image_t *source, \
		t_rectangle paste_slice, t_rectangle copy_slice)
{
	const float		radius = TILE_OFFSET * TILE_SIZE;
	t_vector2dint	copy_point;	
	t_vector2dint	paste_point;
	t_vector2dint	pixel;
	uint32_t		color;

	copy_point.x = 0;
	copy_point.y = 0;
	paste_point.y = 0;
	while (paste_point.y < (int32_t)paste_slice.height)
	{
		paste_point.x = 0;
		while (paste_point.x < (int32_t)paste_slice.width)
		{
			color = copy_next_pixel(source, copy_slice, &copy_point);
			pixel.x = paste_slice.x + paste_point.x;
			pixel.y = paste_slice.y + paste_point.y;
			if (inside_circle(pixel, (t_vector2dint){(paste_slice.x + radius), \
			(paste_slice.y + radius)}, radius))
				mlx_put_pixel(dest, pixel.x, pixel.y, color);
			paste_point.x++;
		}
		paste_point.y++;
	}
}

void	draw_partial_minimap(mlx_image_t *minimap, mlx_image_t *screen, \
		t_vector2d position, t_map *map)
{
	const float			minimap_size = TILE_OFFSET * 2;
	const float			graphic_size = TILE_SIZE * minimap_size;
	const t_rectangle	paste_slice = (t_rectangle){40, 40, \
						graphic_size, graphic_size};
	t_rectangle			copy_slice;

	copy_slice.height = graphic_size;
	copy_slice.width = graphic_size;
	copy_slice.x = (position.x - TILE_OFFSET) * TILE_SIZE;
	copy_slice.y = (position.y - TILE_OFFSET) * TILE_SIZE;
	if (copy_slice.x < 0)
		copy_slice.x = 0;
	if (copy_slice.x >= (map->width - minimap_size) * TILE_SIZE)
		copy_slice.x = (map->width - minimap_size) * TILE_SIZE;
	if (copy_slice.y < 0)
		copy_slice.y = 0;
	if (copy_slice.y >= (map->height - minimap_size) * TILE_SIZE)
		copy_slice.y = (map->height - minimap_size) * TILE_SIZE;
	draw_slice_circle(screen, minimap, paste_slice, copy_slice);
}
