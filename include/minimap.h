/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 22:04:20 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/10 17:51:59 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "utilities.h"
# include "map.h"
# include "MLX42/MLX42.h"
# include "shapes.h"
# ifndef TILE_SIZE
#  define TILE_SIZE 24
# endif
# ifndef TILE_OFFSET
#  define TILE_OFFSET 3
# endif
# ifndef LINE_WEIGHT_PX
#  define LINE_WEIGHT_PX 1
# endif
# ifndef EMPTY_TILE
#  define EMPTY_TILE '@'
# endif
# ifndef WALL_TILE
#  define WALL_TILE '1'
# endif
# ifndef WALK_TILE
#  define WALK_TILE '0'
# endif

typedef enum e_tile
{
	TILE_NONE = -1,
	TILE_EMPTY = 0,
	TILE_WALK,
	TILE_WALL,
	TILE_SPAWN,
	TILE_COUNT
}	t_tile;

uint32_t	get_tile_color(t_tile tile);
void		draw_minimap(t_map *const map, mlx_image_t *minimap);
void		draw_partial_minimap(mlx_image_t *minimap, mlx_image_t *screen, \
			t_vector2d position, t_map *map);
bool		pad_map(t_map *map);
#endif
