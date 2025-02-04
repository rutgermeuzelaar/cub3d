/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 21:19:23 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/04 20:08:26 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "color.h"
#include "raycasting_structs.h"
#include "shapes.h"
#include "cub3d.h"

void	draw_textured_rectangle(t_game *game, t_textured_rectangle rectangle, \
		t_ray_collision collision);
