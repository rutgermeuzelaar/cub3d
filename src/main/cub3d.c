/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:13:18 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/31 17:47:45 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#include "MLX42/MLX42.h"
#include "utilities.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)game;
	if (argc != 2 || argv[1] == NULL || check_os_compatibility() == 1)
		return (EXIT_FAILURE);
	(void)printf("finished parsing\n");
	if (!init_game(&game, argv[1]))
	{
		return (EXIT_FAILURE);
	}
	mlx_loop(game.mlx);
	free_function(&game);
	return (EXIT_SUCCESS);
}
