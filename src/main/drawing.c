/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:30:19 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/02 17:28:30 by rmeuzela      ########   odam.nl         */
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

static void	draw_movement_cross(const float angle, t_vector2d position, \
		mlx_image_t *minimap)
{
	const float	quarter = RADIAN * 45;
	const float	radius = 0.4;
	t_vector2d	circle_point_1;
	t_vector2d	circle_point_2;
	int			i;

	i = 0;
	while (i < 4)
	{
		circle_point_1 = position;
		circle_point_2 = position;
		circle_point_1.x += cos(angle + quarter * (i + 1)) * radius;
		circle_point_1.y += sin(angle + quarter * (i + 1)) * radius;
		circle_point_2.x += position.x - circle_point_1.x;
		circle_point_2.y += position.y - circle_point_1.y;
		draw_line((t_vector2dint){circle_point_1.x * TILE_SIZE, \
		circle_point_1.y * TILE_SIZE}, (t_vector2dint){circle_point_2.x * \
		TILE_SIZE, circle_point_2.y * TILE_SIZE}, minimap, RED);
		i++;
	}
}


#include "textures.h"

void	cheese(t_game *game)
{
	mlx_texture_t	*texture;
	t_vector2dint	point;

	point.y = 0;
	texture = game->textures[0];
	printf("PIETER: %p\n", texture);
	while (point.y < (int)texture->height)
	{
		point.x = 0;
		while (point.x < (int)texture->width)
		{
			mlx_put_pixel(game->screen, point.x, point.y, get_texel(texture, point.x, point.y).rgba);
			point.x++;
		}
		point.y++;
	}
}

void	draw_routine(void *param)
{
	t_game *const	game = (t_game *)param;

	draw_background(game->screen, game->floor, game->ceiling);
	ft_memset(game->minimap->pixels, WHITE, game->minimap->height * \
	game->minimap->width * BPP);
	draw_minimap(&game->map, game->minimap, game->screen);
	draw_player(&game->player, game->minimap);
	draw_movement_cross(game->player.dir_angle, (t_vector2d){game->player.x, \
	game->player.y}, game->minimap);
	cast_ray_all(game);
	draw_partial_minimap(game->minimap, game->screen, (t_vector2d){\
	game->player.x, game->player.y}, &game->map);
}
