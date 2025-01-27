/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_draw.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 22:09:28 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/27 22:05:27 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "minimap.h"
#include "map.h"
#include "shapes.h"
#include "color.h"
#include <math.h>

static void set_fill(char texture, t_vector2dint index2d, mlx_image_t *image)
{
	int				color;
	t_dimensions	dimensions;

	if (texture == '1')
	{
		color = WALL_COLOR;
	}
	else
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

// should only necessary one
void	draw_minimap(t_map *const map, mlx_image_t *minimap, mlx_image_t *screen)
{
	size_t	x;
	size_t	y;

	y = 0;
	(void)screen;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			set_fill(map->map[y][x], (t_vector2dint){x * TILE_SIZE, y * TILE_SIZE}, minimap);
			x++;
		}
		y++;
	}
}

// everything should move per pixel to make it easier
static uint32_t	copy_next_pixel(mlx_image_t *source, t_rectangle copy_slice, \
				t_vector2dint *point)
{
	t_color		color;
	int			i;

	i = 0;
	color.rgba = PINK;
	if (point->y == (int32_t)copy_slice.height)
	{
		return (color.rgba);
	}
	if (point->x < (int32_t)copy_slice.width)
	{
		i = ((int)copy_slice.x + point->x  + (((int)copy_slice.y + point->y) * source->width)) * 4;
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

void	draw_slice(mlx_image_t *dest, mlx_image_t *source, \
		t_rectangle paste_slice, t_rectangle copy_slice)
{
	t_vector2dint	copy_point;	
	t_vector2dint	paste_point;

	copy_point.x = 0;
	copy_point.y = 0;
	paste_point.y = 0; 
	while (paste_point.y < (int32_t)paste_slice.height)
	{
		paste_point.x = 0;
		while (paste_point.x < (int32_t)paste_slice.width)
		{
			mlx_put_pixel(dest, paste_slice.x + paste_point.x, paste_slice.y + paste_point.y, copy_next_pixel(source, copy_slice, &copy_point));
			paste_point.x++;
		}
		paste_point.y++;
	}
}

static bool	inside_circle(t_vector2dint point, t_vector2dint circle_center, \
			const float radius)
{
	return ((pow(point.x - circle_center.x, 2) + pow(point.y - circle_center.y, 2)) < pow(radius, 2));
}

void	draw_slice_circle(mlx_image_t *dest, mlx_image_t *source, \
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
			if (inside_circle(pixel, (t_vector2dint){(paste_slice.x + radius), (paste_slice.y + radius)}, radius))
			{
				mlx_put_pixel(dest, pixel.x, pixel.y,color);
			}
			paste_point.x++;
		}
		paste_point.y++;
	}
}


void	draw_partial_minimap(mlx_image_t *minimap, mlx_image_t *screen, \
		t_vector2d position, t_map *map)
{
	const float	minimap_size = TILE_OFFSET * 2;
	t_rectangle	paste_slice;
	t_rectangle	copy_slice;

	copy_slice.height = TILE_SIZE * minimap_size;
	copy_slice.width = TILE_SIZE * minimap_size;
	copy_slice.x = (position.x - TILE_OFFSET) * TILE_SIZE;
	copy_slice.y = (position.y - TILE_OFFSET) * TILE_SIZE;
	paste_slice.height = copy_slice.height;
	paste_slice.width = copy_slice.width;
	paste_slice.x = 40;
	paste_slice.y = 40;
	printf("DOG w: %d h: %d\n", paste_slice.width, paste_slice.width);
	// draw_rectangle(screen, paste_slice, LIME);
	if (copy_slice.x < 0)
	{
		copy_slice.x = 0;
	}
	if (copy_slice.x >= (map->width - minimap_size) * TILE_SIZE)
	{
		copy_slice.x = (map->width - minimap_size) * TILE_SIZE;
	}
	if (copy_slice.y < 0)
	{
		copy_slice.y = 0;	
	}
	if (copy_slice.y >= (map->height - minimap_size) * TILE_SIZE)
	{
		copy_slice.y = (map->height - minimap_size) * TILE_SIZE;
	}
	draw_slice_circle(screen, minimap, paste_slice, copy_slice);
}
