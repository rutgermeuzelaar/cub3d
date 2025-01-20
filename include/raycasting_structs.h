/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_structs.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 15:16:12 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/20 20:00:08 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_STRUCTS_H
# define RAYCASTING_STRUCTS_H
# include "shapes.h"

typedef enum e_cardinal_direction
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
}	t_cardinal_direction;

typedef struct s_ray
{
	t_vector2d				position;
	t_vector2d				direction;
	t_cardinal_direction	cardinal;
	float					angle;
	float					distance;
}	t_ray;

typedef struct s_ray_collision
{
	bool					hit;
	t_vector2d				point;
	t_cardinal_direction	cardinal;
	float					distance;
}	t_ray_collision;
#endif
