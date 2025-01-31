/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 21:19:23 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/31 21:58:23 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "color.h"
#include "raycasting_structs.h"
#include "shapes.h"
#include "cub3d.h"

t_color			get_texel(mlx_texture_t *texture, const float x, const float y);
mlx_texture_t	*get_texture_cardinal(t_cardinal_direction cardinal, \
				mlx_texture_t **textures);
void			draw_texture_stripe(t_game *game, const t_rectangle stripe, \
				const t_ray_collision collision);
