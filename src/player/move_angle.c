/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nilsleusden@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:02:47 by rmeuzela          #+#    #+#             */
/*   Updated: 2025/02/14 00:00:03 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE
#include <math.h>
#include "player.h"
#include "raycasting.h"

void	move_angle_right(t_player *player)
{
	player->dir_angle += ROTATION_SPEED;
	if (player->dir_angle >= (2 * M_PI))
	{
		player->dir_angle -= 2 * M_PI;
	}
	player->dir_x = cos(player->dir_angle);
	player->dir_y = sin(player->dir_angle);
	set_ray_angles(player->rays, player);
}

void	move_angle_left(t_player *player)
{
	player->dir_angle -= ROTATION_SPEED;
	if (player->dir_angle <= 0)
	{
		player->dir_angle += 2 * M_PI;
	}
	player->dir_x = cos(player->dir_angle);
	player->dir_y = sin(player->dir_angle);
	set_ray_angles(player->rays, player);
}
