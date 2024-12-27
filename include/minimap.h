/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 22:04:20 by rmeuzela      #+#    #+#                 */
/*   Updated: 2024/12/27 20:45:24 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif
# ifndef WALL_COLOR
#  define WALL_COLOR 0x000080
# endif
# ifndef FLOOR_COLOR
#  define FLOOR_COLOR 0xffc0cb
# endif
# ifndef LINE_WEIGHT_PX
#  define LINE_WEIGHT_PX 1
# endif
# include "map.h"
# include "MLX42/MLX42.h"

void	draw_minimap(t_map *const map, mlx_image_t *image);
#endif
