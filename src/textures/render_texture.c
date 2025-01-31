/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_texture.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 15:15:36 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/31 22:33:23 by rmeuzela      ########   odam.nl         */
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

t_color	get_texel(mlx_texture_t *texture, const float x, const float y)
{
	const uint32_t	texture_surface = texture->height * texture->width;
	t_color			texel;
	int				i;

	i = 0;
	printf("texel x: %f y: %f\n", x, y);
	i = (y * texture->width + x) * BPP;
	assert((int)i / 4 < (int)texture_surface);
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

// void	draw_texture_slice(mlx_image_t *image, mlx_texture_t *texture, 
// 		const float x, const int height)
// {
// 	const float	pixel_size = texture->height / height;
// 	t_vector2d	texture_point;
// 	t_color		texel;
// 	int			i;

// 	int	size;

// 	i = 0;
// 	texture_point.x = x;
// 	texture_point.y = 0;
// 	while (i < height)
// 	{
// 		texel = get_texel(texture, texture_point.x, texture_point.y);
// 		i = pixel_size;
// 		while (true)
// 		{
// 			mlx_put_pixel(image, 0, 0, texel.rgba);
// 		}
// 	}
// }

void	draw_texture_stripe(t_game *game, const t_rectangle stripe, \
		const t_ray_collision collision)
{
	mlx_texture_t *const	texture = get_texture_cardinal(collision.cardinal, \
							game->textures);
	const float				step_size = stripe.height / texture->height;
	float					steps;
	t_color					texel;
	float					new_x;
	double	temp;
	t_rectangle				skib;


	steps = 0;
	printf("texture height: %d\n", texture->height);
	printf("step_size: %f\n", step_size);
	while ((int)steps < (int)stripe.height)
	{
		skib = stripe;
		skib.y += (int)steps;
		new_x = modf(collision.point.x, &temp) * texture->width;
		printf("colx: %f new_x: %f\n", collision.point.x, new_x);
		texel = get_texel(texture, new_x, steps);
		draw_rectangle(game->screen, skib, texel.rgba);
		steps += step_size;
	}
}
