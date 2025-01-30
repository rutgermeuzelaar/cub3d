/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 13:21:49 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/30 14:43:56 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# ifndef RADIAN
#  define RADIAN 0.01745329f
# endif
# include "MLX42/MLX42.h"
# include "shapes.h"
# include "player.h"
# include "map.h"
# include "raycasting_structs.h"
# include "cub3d.h"

bool			almost_equal(float a, float b);
void			set_ray_angles(t_ray *rays, t_player *player);
void			cast_ray_all(t_game *game);
t_ray_collision	cast_ray(t_ray *ray, t_map *map, mlx_image_t *minimap);
t_vector2d		get_delta_distance(const float tan_value);
void			cast_ray_helper(t_cast_xl *cast_xl, t_map *map, \
				mlx_image_t *minimap, t_ray *ray);
#endif
