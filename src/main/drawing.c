/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:30:19 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/13 17:18:29 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "MLX42/MLX42.h"
#include "color.h"
#include "shapes.h"
#include "raycasting.h"
#include "cub3d.h"
#include "libft.h"
#include "minimap.h"
#include "player.h"

static void	draw_background(mlx_image_t *screen, const t_color floor, \
			const t_color ceiling)
{
	const int	half_window_height = WINDOW_HEIGHT / 2;

	draw_rectangle(screen, \
	(t_rectangle){0, 0, WINDOW_WIDTH, half_window_height}, ceiling.rgba);
	draw_rectangle(screen, \
	(t_rectangle){0, half_window_height, WINDOW_WIDTH, half_window_height}, \
	floor.rgba);
}

void	draw_routine(void *param)
{
	t_game *const	game = (t_game *)param;

	draw_background(game->screen, game->floor, game->ceiling);
	draw_rectangle(game->minimap, (t_rectangle){0, 0, game->minimap->width, \
	game->minimap->height}, get_tile_color(TILE_EMPTY));
	draw_minimap(&game->map, game->minimap);
	draw_player(&game->player, game->minimap);
	cast_ray_all(game);
	draw_partial_minimap(game->minimap, game->screen, (t_vector2d){\
	game->player.x, game->player.y}, &game->map);
}
