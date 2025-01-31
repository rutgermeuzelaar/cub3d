/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:13:18 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/31 19:49:49 by rmeuzela      ########   odam.nl         */
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

// typedef struct s_color_pair
// {
// 	const char		*name;
// 	const uint32_t	value;
// }	t_color_pair;

// int	main(void)
// {
// 	const t_color_pair colors[] = {
// 		(t_color_pair){"LIGHTGRAY", LIGHTGRAY},
// 		(t_color_pair){"GRAY", GRAY},
// 		(t_color_pair){"DARKGRAY", DARKGRAY},
// 		(t_color_pair){"YELLOW", YELLOW},
// 		(t_color_pair){"GOLD", GOLD},
// 		(t_color_pair){"ORANGE", ORANGE},
// 		(t_color_pair){"PINK", PINK},
// 		(t_color_pair){"RED", RED},
// 		(t_color_pair){"MAROON", MAROON},
// 		(t_color_pair){"GREEN", GREEN},
// 		(t_color_pair){"LIME", LIME},
// 		(t_color_pair){"DARKGREEN", DARKGREEN},
// 		(t_color_pair){"SKYBLUE", SKYBLUE},
// 		(t_color_pair){"BLUE", BLUE},
// 		(t_color_pair){"DARKBLUE", DARKBLUE},
// 		(t_color_pair){"PURPLE", PURPLE},
// 		(t_color_pair){"VIOLET", VIOLET},
// 		(t_color_pair){"DARKPURPLE", DARKPURPLE},
// 		(t_color_pair){"BEIGE", BEIGE},
// 		(t_color_pair){"BROWN", BROWN},
// 		(t_color_pair){"DARKBROWN", DARKBROWN},
// 		(t_color_pair){"WHITE", WHITE},
// 		(t_color_pair){"BLACK", BLACK},
// 		(t_color_pair){"BLANK", BLANK},
// 		(t_color_pair){"MAGENTA", MAGENTA},
// 	};

// 	int	i;

// 	i = 0;
// 	while (i < 25)
// 	{
// 		printf("# define %s %u\n", colors[i].name, colors[i].value);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }
