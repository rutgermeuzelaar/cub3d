/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 13:21:49 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/19 15:17:06 by rmeuzela      ########   odam.nl         */
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

bool	point_out_of_bounds(t_vector2d *point, const uint32_t height, \
		const uint32_t width);
int		ceil_multiple(float number, int multiple);
int		floor_multiple(float number, int multiple);
void	set_ray_distance(t_ray *ray, t_ray_collision *collision);
void	cast_ray_horizontal(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap);
void	cast_ray_vertical(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap);
bool	almost_equal(float a, float b);
void	set_ray_angles(t_ray *rays, t_player *player);
t_ray_collision	get_ray_collision_horizontal(t_ray *ray, t_map *map, mlx_image_t *minimap);
t_ray_collision	get_ray_collision_vertical(t_ray *ray, t_map *map);
float	cast_ray(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap);
void	cast_ray_all(t_ray *rays, t_player *player, t_map *map, mlx_image_t *minimap);
#endif
