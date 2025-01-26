/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_structs.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 15:16:12 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/26 20:15:51 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_STRUCTS_H
# define RAYCASTING_STRUCTS_H
# include "shapes.h"

typedef enum e_cardinal_direction
{
	CARDINAL_NONE = -1,
	NORTH = 0,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST,
	CARDINAL_COUNT
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
