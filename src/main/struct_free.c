/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_free.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 13:13:05 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/31 17:50:54 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "map.h"
#include "player.h"
#include "cub3d.h"
#include "utilities.h"

void	free_function(t_game *game)
{
	free(game->file_content);
	arr_free((void **)game->map.map);
	mlx_terminate(game->mlx);
	free(game->textures);
	free(game->player.rays);
	printf("free'd resources\n");
	return ;
}
