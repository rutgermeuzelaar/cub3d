/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_texture.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 15:15:36 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/31 18:58:18 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
