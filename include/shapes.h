/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/27 10:16:48 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/01 21:58:05 by rmeuzela      ########   odam.nl         */
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
	uint32_t	x;
	uint32_t	y;
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

void	draw_rectangle(mlx_image_t *image, t_rectangle rectangle, \
		uint32_t color);
void	draw_line(int x1, int y1, int x2, int y2, mlx_image_t *image, \
		uint32_t color);
#endif
