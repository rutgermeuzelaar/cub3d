/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/30 20:59:29 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/27 21:19:52 by rmeuzela      ########   odam.nl         */
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
#  define ROTATION_SPEED 0.03f
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

bool	is_colliding(t_vector2d point, t_map *map);
bool	init_player(t_player *const player, float spawn_x, float spawn_y);
void	move_player(void *param);
void	draw_player(const t_player *const player, mlx_image_t *minimap);
bool	collide_circle(t_vector2d position, t_map *map, const float radius, \
		mlx_image_t *minimap);
#endif
