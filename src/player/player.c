/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 16:20:18 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/20 20:24:07 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "shapes.h"
#include "libft.h"
#include "player.h"
#include "utilities.h"
#include "map.h"
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "raycasting.h"

bool	init_player(t_player *const player, float spawn_x, float spawn_y)
{
	player->ray_count = 240;
	player->rays = ft_calloc(player->ray_count, sizeof(t_ray));
	if (!player->rays)
	{
		return (false);
	}
	player->color.rgba = VIOLET;
	player->ray_color.rgba = YELLOW;
	player->x = spawn_x;
	player->y = spawn_y;
	player->height = 0.25;
	player->width = 0.25;
	player->dir_angle = 0;
	set_ray_angles(player->rays, player);
	player->dir_x = cos(player->dir_angle);
	player->dir_y = sin(player->dir_angle);
	return (true);	
}

void	draw_player(const t_player *const player, mlx_image_t *minimap)
{
	t_vector2dint	direction;
	t_rectangle		player_icon;

	direction.x = (player->x + (player->dir_x * 0.5)) * TILE_SIZE;
	direction.y = (player->y + (player->dir_y * 0.5)) * TILE_SIZE;
	player_icon.x = (player->x - player->width / 2) * TILE_SIZE;
	player_icon.y = (player->y - player->height / 2) * TILE_SIZE;
	player_icon.height = player->height * TILE_SIZE;
	player_icon.width = player->width * TILE_SIZE;
	draw_rectangle(minimap, player_icon, player->color.rgba);
	draw_line((t_vector2dint){player->x * TILE_SIZE, player->y * TILE_SIZE}, \
	direction, minimap, player->color.rgba);
}
