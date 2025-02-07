/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terminate.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/07 22:39:10 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/07 23:36:30 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINATE_H
# define TERMINATE_H
# include <stdlib.h>

typedef void	(*t_terminate_func)(void *);

typedef struct s_termination
{
	const t_terminate_func	*layers;
	size_t					current_layer;
}	t_termination;

void	terminate_layered(void *param, t_termination termination);
void	terminate_map(void *param);
void	terminate_mlx_wrapper(void *param);
void	terminate_textures(void *param);
void	terminate_player(void *param);
#endif