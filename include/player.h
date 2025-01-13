/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/30 20:59:29 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/13 15:41:27 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "color.h"
# include "shapes.h"
# ifndef MOVE_STEPS
#  define MOVE_STEPS 400
# endif
# ifndef ROTATION_SPEED
#  define ROTATION_SPEED 0.1f
# endif
# ifndef DIRECTION_LINE_LENGTH
#  define DIRECTION_LINE_LENGTH 40
# endif

typedef struct s_player
{
	t_rectangle		rectangle;
	t_rectangle		dir;
	t_ray			ray; // make array later
	t_color			color;
	t_color			ray_color;
	float			x;
	float			y;
	float			dir_x;
	float			dir_y;
	float			dir_angle;
}	t_player;

void	init_player(t_player *const player, float spawn_x, float spawn_y);
void	move_player(void *param);
void	draw_player(const t_player *const player, mlx_image_t *minimap);
#endif
