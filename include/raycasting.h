/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 13:21:49 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/17 16:43:53 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "MLX42/MLX42.h"
# include "shapes.h"
# include "player.h"
# include "map.h"

bool	point_out_of_bounds(t_vector2d *point, const uint32_t height, \
		const uint32_t width);
void	cast_ray_horizontal(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap);
void	cast_ray_vertical(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap);
void	cast_ray(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap);
#endif
