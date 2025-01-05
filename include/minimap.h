/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 22:04:20 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/04 13:50:52 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "utilities.h"
# ifndef TILE_SIZE
#  define TILE_SIZE 64
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

void	draw_minimap(t_map *const map, mlx_image_t *image);
#endif
