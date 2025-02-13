/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:13:18 by nleusden      #+#    #+#                 */
/*   Updated: 2025/02/13 16:57:05 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "cub3d.h"
#include "MLX42/MLX42.h"
#include "utilities.h"
#include "terminate.h"

int	main(int argc, char **argv)
{
	t_game			game;
	t_termination	termination;

	ft_memset(&game, 0, sizeof(t_game));
	termination.layers = (t_terminate_func[]){terminate_map, \
	terminate_textures, terminate_mlx_wrapper, terminate_player};
	termination.current_layer = 0;
	if (argc != 2 || argv[1] == NULL || check_os_compatibility() == 1)
		return (printf("Error arguments\n"), EXIT_FAILURE);
	if (!init_game(&game, argv[1], &termination))
	{
		return (EXIT_FAILURE);
	}
	mlx_loop(game.mlx);
	terminate_layered((void *)&game, termination);
	return (EXIT_SUCCESS);
}
