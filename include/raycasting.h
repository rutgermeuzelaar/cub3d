/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 13:21:49 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/13 14:52:13 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "MLX42/MLX42.h"
# include "shapes.h"
# include "player.h"
# include "map.h"

void	cast_ray_horizontal(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap);
void	cast_ray_vertical(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap);
void	cast_ray(t_ray *ray, t_player *player, t_map *map, \
		mlx_image_t *minimap);
#endif
