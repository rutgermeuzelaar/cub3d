/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 12:46:01 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/17 17:54:01 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "player.h"
#include "map.h"
#include "minimap.h"
#include "raycasting.h"

void	cast_ray(t_ray *ray, t_player *player, t_map *map, mlx_image_t *minimap)
{
	if (!(player->dir_angle == M_PI || player->dir_angle == 0))
	{
		cast_ray_horizontal(ray, player, map, minimap);
	}
	// if (!(player->dir_angle == (M_PI / 2) || 
	// player->dir_angle == ((3 * M_PI) / 2)))
	// {
	// 	cast_ray_vertical(ray, player, map, minimap);	
	// }
}
