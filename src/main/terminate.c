/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terminate.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/07 22:39:35 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/07 23:36:10 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "terminate.h"
#include "utilities.h"

void	terminate_layered(void *param, t_termination termination)
{
	size_t	i;

	i = 0;
	while (i < termination.current_layer)
	{
		termination.layers[i](param);
		i++;
	}
}

void	terminate_map(void *param)
{
	t_game *const	game = (t_game *)param;

	free_pointer_array((void **)game->map.map, game->map.height);
}

void	terminate_mlx_wrapper(void *param)
{
	t_game *const	game = (t_game *)param;

	mlx_terminate(game->mlx);
}

void	terminate_textures(void *param)
{
	t_game *const	game = (t_game *)param;
	int				i;

	i = 0;
	while (game->textures[i])
	{
		mlx_delete_texture(game->textures[i]);
		i++;
	}
	free(game->textures);
}

void	terminate_player(void *param)
{
	t_game *const	game = (t_game *)param;

	free(game->player.rays);
}
