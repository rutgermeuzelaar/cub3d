/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 21:19:23 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/03 16:25:43 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "color.h"
#include "raycasting_structs.h"
#include "shapes.h"
#include "cub3d.h"

t_color			get_texel(mlx_texture_t *texture, const int x, const int y);
mlx_texture_t	*get_texture_cardinal(t_cardinal_direction cardinal, \
				mlx_texture_t **textures);
void	draw_texture_slice(t_game *game, t_ray_collision collision, 
		const float x, t_vector2dint image_point, const float distance, \
		const float texture_y, const float old_distance);

void	draw_textured_rectangle(t_game *game, t_rectangle rectangle, \
		t_ray_collision collision, const float texture_y, const float old_distance);
