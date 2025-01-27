/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 22:04:20 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/27 21:14:50 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "utilities.h"
# ifndef TILE_SIZE
#  define TILE_SIZE 24
# endif
# ifndef WALL_COLOR
#  define WALL_COLOR get_rgba(0x000000, 255)
# endif
# ifndef FLOOR_COLOR
#  define FLOOR_COLOR get_rgba(0x808080, 255)
# endif
# ifndef LINE_WEIGHT_PX
#  define LINE_WEIGHT_PX 1
# endif
# include "map.h"
# include "MLX42/MLX42.h"
# include "shapes.h"

void	draw_minimap(t_map *const map, mlx_image_t *minimap, mlx_image_t *screen);
void	draw_slice(mlx_image_t *dest, mlx_image_t *source, \
		t_rectangle paste_slice, t_rectangle copy_slice);
void	draw_partial_minimap(mlx_image_t *minimap, mlx_image_t *screen, \
		t_vector2d position, t_map *map);
#endif
