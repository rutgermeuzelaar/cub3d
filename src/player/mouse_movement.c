/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nilsleusden@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:37:43 by nleusden          #+#    #+#             */
/*   Updated: 2025/02/14 00:10:41 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include "player.h"
#include "MLX42/MLX42.h"
#include "shapes.h"
#include "cub3d.h"
#include "raycasting.h"
#include "raycasting_structs.h"
#include <stdio.h>
#include <unistd.h>

void	rotate_player(t_player *player, float direction, float sens)
{
	player->dir_angle += (direction * sens);
	player->dir_angle = fmod(player->dir_angle, 2 * M_PI);
	if (player->dir_angle < 0)
		player->dir_angle += 2 * M_PI;
	player->dir_x = cos(player->dir_angle);
	player->dir_y = sin(player->dir_angle);
}

void	mouse_support(mlx_t *mlx, t_player *player, mlx_image_t *screen)
{
	int				pos[2];
	static double	time;
	static bool		mouse;
	int				x;

	if (mlx_is_mouse_down(mlx, 0) && (time + 0.25 < mlx_get_time()))
	{
		mouse = !mouse;
		time = mlx_get_time();
		mlx_set_mouse_pos(mlx, (screen->width / 2), (screen->height / 2));
		mlx_set_cursor_mode(mlx, MLX_MOUSE_NORMAL + mouse);
	}
	if (!mouse)
		return ;
	mlx_get_mouse_pos(mlx, &pos[0], &pos[1]);
	mlx_set_mouse_pos(mlx, screen->width / 2, screen->height / 2);
	x = pos[0] - (screen->width / 2);
	if (x < 0)
		rotate_player(player, -1, 0.03f);
	else if (x > 0)
		rotate_player(player, 1, 0.03f);
	set_ray_angles(player->rays, player);
}
