/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nilsleusden@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:13:18 by nleusden          #+#    #+#             */
/*   Updated: 2024/12/22 16:00:10 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game_struct;

	if (argc != 2 && argv[1] == NULL)
		return (ERROR);
	game_struct = ft_calloc(2, sizeof(t_game));
	if (!game_struct)
		return (ERROR);
	if (check_file(argv[1], game_struct) == SUCCESS)
	{
		print_arr(game_struct->map);
		return (SUCCESS);
	}
	return (ERROR);
}

