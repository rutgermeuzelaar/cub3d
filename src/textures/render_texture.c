/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_texture.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 15:15:36 by nleusden      #+#    #+#                 */
/*   Updated: 2025/02/03 16:33:41 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "raycasting_structs.h"
#include "shapes.h"
#include "cub3d.h"
#include "utilities.h"

int	texture_loading_main(t_ray_collision *collision)
{
	t_ray_collision *ray_y;

	ray_y = collision;
	
	printf("y = %f\n", ray_y->point.y);
	return (SUCCESS);
}

t_color	get_texel(mlx_texture_t *texture, const int x, const int y)
{
	const uint32_t	texture_surface = texture->height * texture->width;
	t_color			texel;
	int				i;

	i = 0;
	i = (y * texture->width + x) * BPP;
	// printf("texel x: %d y: %d\n", x, y);
	assert((int)i / 4 <= (int)texture_surface);
	texel.bytes.red = texture->pixels[i];
	texel.bytes.green = texture->pixels[i + 1];
	texel.bytes.blue = texture->pixels[i + 2];
	texel.bytes.alpha = texture->pixels[i + 3];
	return (texel);
}

mlx_texture_t	*get_texture_cardinal(t_cardinal_direction cardinal, \
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

void	draw_texture_slice(t_game *game, t_ray_collision collision, 
		const float x, t_vector2dint image_point, const float distance, \
		const float texture_y, const float old_distance)
{
	mlx_texture_t *const	texture = get_texture_cardinal(collision.cardinal, \
							game->textures);
	t_vector2d				texture_point;
	t_color					texel;
	float					pixel_size;
	int						i;

	texture_point.x = x;
	pixel_size = texture->height / old_distance;
	texture_point.y = pixel_size * (texture_y);
	assert(pixel_size > 0);
	i = 0;
	while (i < distance && (uint32_t)texture_point.y < texture->height)
	{
		texel = get_texel(texture, texture_point.x, texture_point.y);
		if (collision.cardinal == EAST || collision.cardinal == WEST)
		{
			texel.bytes.red /= 2;
			texel.bytes.green /= 2;
			texel.bytes.blue /= 2;
		}
		mlx_put_pixel(game->screen, image_point.x, image_point.y + i, texel.rgba);
		texture_point.y += pixel_size;
		i++;
	}
}

void	draw_textured_rectangle(t_game *game, t_rectangle rectangle, \
		t_ray_collision collision, const float texture_y, const float old_distance)
{
	double	temp;
	int		texture_x;
	int		i;

	i = 0;
	texture_x = modf(collision.point.x, &temp) * game->textures[0]->width;
	while (i < (int)rectangle.width)
	{
		draw_texture_slice(game, collision, texture_x, \
		(t_vector2dint){rectangle.x + i, rectangle.y}, rectangle.height, \
		texture_y, old_distance);
		i++;
	}
}
