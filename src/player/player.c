/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 16:20:18 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/14 19:57:19 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include "shapes.h"
#include "libft.h"
#include "player.h"
#include "MLX42/MLX42.h"
#include "minimap.h"
#include "raycasting_structs.h"
#include "raycasting.h"
#include "color.h"

static void	set_player_angle(t_player *player, t_cardinal_direction cardinal)
{
	assert(cardinal != CARDINAL_NONE && cardinal != CARDINAL_COUNT);
	if (cardinal == NORTH)
	{
		player->dir_angle = M_PI_2 * 3;
	}
	if (cardinal == EAST)
	{
		player->dir_angle = M_PI_2 * 4;
	}
	if (cardinal == SOUTH)
	{
		player->dir_angle = M_PI_2;
	}
	if (cardinal == WEST)
	{
		player->dir_angle = M_PI_2 * 2;
	}
}

bool	init_player(t_player *const player, float spawn_x, float spawn_y, \
		t_cardinal_direction cardinal)
{
	player->ray_count = WINDOW_WIDTH;
	player->rays = ft_calloc(player->ray_count, sizeof(t_ray));
	if (!player->rays)
	{
		return (false);
	}
	player->color.rgba = VIOLET;
	player->ray_color.rgba = YELLOW;
	player->x = spawn_x;
	player->y = spawn_y;
	player->height = 0.5;
	player->width = 0.5;
	set_player_angle(player, cardinal);
	set_ray_angles(player->rays, player);
	player->dir_x = cos(player->dir_angle);
	player->dir_y = sin(player->dir_angle);
	return (true);
}

void	draw_player(const t_player *const player, mlx_image_t *minimap)
{
	t_rectangle		player_icon;

	player_icon.x = (player->x - player->width / 2) * TILE_SIZE;
	player_icon.y = (player->y - player->height / 2) * TILE_SIZE;
	player_icon.height = player->height * TILE_SIZE;
	player_icon.width = player->width * TILE_SIZE;
	draw_rectangle(minimap, player_icon, player->color.rgba);
}
