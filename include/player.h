/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/30 20:59:29 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/01 01:04:23 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include <inttypes.h>
# include "shapes.h"

typedef struct s_player
{
	t_rectangle		rectangle;	
	int32_t			color;
}	t_player;

void	move_player(void *param);
#endif
