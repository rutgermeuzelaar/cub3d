/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 16:20:18 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/01 01:11:35 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "player.h"

void	init_player(t_player *player)
{
	player->color = 0x11abce1;
	player->rectangle.height = 16;
	player->rectangle.width = 16;
	player->rectangle.x = 50;
	player->rectangle.y = 50;
}
