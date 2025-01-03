/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/30 20:59:29 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/03 01:08:01 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include <inttypes.h>
# include "shapes.h"
# ifndef MOVE_STEPS
#  define MOVE_STEPS 400
# endif

typedef struct s_player
{
	t_rectangle		rectangle;
	t_rectangle		dir;
	int32_t			color;
	float			dir_x;
	float			dir_y;
	float			dir_angle;
}	t_player;

void	init_player(t_player *const player);
void	move_player(void *param);
void	draw_player(const t_player *const player, mlx_image_t *minimap);
#endif
