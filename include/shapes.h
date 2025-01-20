/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/27 10:16:48 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/18 20:30:48 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H
# include <inttypes.h>
# include "MLX42/MLX42.h"
# ifndef BPP
#  define BPP sizeof(int32_t)
# endif

typedef struct s_vector2d
{
	float	x;
	float	y;
}	t_vector2d;

typedef struct s_vector2dint
{
	int32_t	x;
	int32_t	y;
}	t_vector2dint;

typedef struct s_dimensions
{
	uint32_t	width;
	uint32_t	height;
}	t_dimensions;

typedef struct s_rectangle
{
	float		x;
	float		y;
	uint32_t	width;
	uint32_t	height;
}	t_rectangle;

typedef struct s_ray
{
	t_vector2d	position;
	t_vector2d	direction;
	float		angle;
}	t_ray;

typedef struct s_ray_collision
{
	bool		hit;
	t_vector2d	point;
	float		distance;
}	t_ray_collision;

void	draw_rectangle(mlx_image_t *image, t_rectangle rectangle, \
		uint32_t color);
void	draw_line_horizontal(t_vector2dint point_1, t_vector2dint point_2, \
		mlx_image_t *image, uint32_t color);
void	draw_line_vertical(t_vector2dint point_1, t_vector2dint point_2, \
		mlx_image_t *image, uint32_t color);
void	draw_line(t_vector2dint point_1, t_vector2dint point_2, \
		mlx_image_t *image, uint32_t color);
void	draw_circle_line(mlx_image_t *image, t_vector2d center, float radius, \
		int32_t color);
#endif
