/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_texture.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 15:15:36 by nleusden      #+#    #+#                 */
/*   Updated: 2025/02/04 20:20:46 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "raycasting_structs.h"
#include "shapes.h"
#include "cub3d.h"
#include "utilities.h"
#include "minimap.h"

static t_color	get_texel(mlx_texture_t *texture, const int x, const int y)
{
	const uint32_t	texture_surface = texture->height * texture->width;
	t_color			texel;
	int				i;

	i = 0;
	i = (y * texture->width + x) * BPP;
	assert((int)i / BPP <= (int)texture_surface);
	texel.bytes.red = texture->pixels[i];
	texel.bytes.green = texture->pixels[i + 1];
	texel.bytes.blue = texture->pixels[i + 2];
	texel.bytes.alpha = texture->pixels[i + 3];
	return (texel);
}

static mlx_texture_t	*get_texture_cardinal(t_cardinal_direction cardinal, \
						mlx_texture_t **textures)
{
	if (cardinal == NORTH)
	{
		return (textures[0]);
	}
	if (cardinal == EAST)
	{
		return (textures[1]);
	}
	if (cardinal == SOUTH)
	{
		return (textures[2]);
	}
	if (cardinal == WEST)
	{
		return (textures[3]);
	}
	return (NULL);
}

static void	draw_texture_slice(t_game *game, t_ray_collision collision, \
			t_textured_rectangle rectangle)
{
	t_color					texel;
	const float				pixel_size = rectangle.texture->height / \
							rectangle.scale_distance;
	int						i;

	rectangle.texture_y *= pixel_size;
	assert(pixel_size > 0);
	i = 0;
	while (i < (int32_t)rectangle.height && (uint32_t)rectangle.texture_y < \
	rectangle.texture->height)
	{
		texel = get_texel(rectangle.texture, rectangle.texture_x, \
		rectangle.texture_y);
		if (collision.cardinal == EAST || collision.cardinal == WEST)
		{
			texel.bytes.red /= 2;
			texel.bytes.green /= 2;
			texel.bytes.blue /= 2;
		}
		mlx_put_pixel(game->screen, rectangle.x, rectangle.y + i, texel.rgba);
		rectangle.texture_y += pixel_size;
		i++;
	}
}

void	draw_textured_rectangle(t_game *game, t_textured_rectangle rectangle, \
		t_ray_collision collision)
{
	double	temp;
	int		i;

	i = 0;
	rectangle.texture = get_texture_cardinal(collision.cardinal, \
	game->textures);
	rectangle.texture_x = modf(collision.point.x, &temp) * \
	rectangle.texture->width;
	while (i < (int)rectangle.width)
	{
		draw_texture_slice(game, collision, rectangle);
		rectangle.x += 1;
		i++;
	}
}
