/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 13:21:49 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/10 13:25:00 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "MLX42/MLX42.h"
# include "shapes.h"
# include "player.h"
# include "map.h"

t_vector2d	get_nearest_hit(t_player *player, t_map *map, float angle, \
			mlx_image_t *minimap);
void		draw_ray(t_player *player, t_map *map, mlx_image_t *minimap, \
			t_ray *ray);
#endif
