/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nilsleusden@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:59:29 by rmeuzela          #+#    #+#             */
/*   Updated: 2025/02/13 01:28:22 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "color.h"
# include "shapes.h"
# include "map.h"
# include "raycasting_structs.h"
# ifndef MOVE_STEPS
#  define MOVE_STEPS 3.0f
# endif
# ifndef ROTATION_SPEED
#  define ROTATION_SPEED 0.06f
# endif
# ifndef DIRECTION_LINE_LENGTH
#  define DIRECTION_LINE_LENGTH 1
# endif

typedef struct s_player
{
	int				ray_count;
	t_ray			*rays;
	t_color			color;
	t_color			ray_color;
	float			x;
	float			y;
	float			width;
	float			height;
	float			dir_x;
	float			dir_y;
	float			dir_angle;
}	t_player;

void	move_angle_right(t_player *player);
void	move_angle_left(t_player *player);
bool	init_player(t_player *const player, float spawn_x, float spawn_y, \
		t_cardinal_direction cardinal);
void	move_player(void *param);
void	draw_player(const t_player *const player, mlx_image_t *minimap);
bool	collide_circle(const t_vector2d position, t_map *map, \
		const float radius);
void	mouse_support(mlx_t *mlx, t_player *player, mlx_image_t *screen);

#endif
