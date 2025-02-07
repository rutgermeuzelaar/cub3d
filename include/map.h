/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/27 10:49:36 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/07 20:37:01 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stdlib.h>
# include "raycasting_structs.h"

typedef struct s_map
{
	char					**map;
	int						player_x;
	int						player_y;
	t_cardinal_direction	cardinal;
	size_t					width;
	size_t					height;
}	t_map;
#endif
