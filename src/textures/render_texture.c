/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:15:36 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/23 16:42:39 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utilities.h"

int	texture_loading_main(t_ray_collision *collision)
{
	t_ray_collision *ray_y;

	ray_y = collision;
	
	printf("y = %f\n", ray_y->point.y);
	return (SUCCESS);
}
