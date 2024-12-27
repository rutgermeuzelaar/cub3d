/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/27 10:16:48 by rmeuzela      #+#    #+#                 */
/*   Updated: 2024/12/27 19:40:17 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H
# ifndef BPP
#  define BPP sizeof(int32_t)
# endif

typedef struct s_vector2d
{
	float	x;
	float	y;
}	t_vector2d;

typedef struct s_index2d
{
	uint32_t	x;
	uint32_t	y;
}	t_index2d;

typedef struct s_dimensions
{
	uint32_t	width;
	uint32_t	height;
}	t_dimensions;
#endif
