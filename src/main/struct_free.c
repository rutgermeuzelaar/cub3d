/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:13:05 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/27 13:12:13 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utilities.h"

void	free_function(t_game *game)
{
	free(game->file_content);
	arr_free((void **)game->map.map);
	mlx_terminate(game->mlx);
	free(game->textures);
	printf("free'd resources\n");
	return ;
}
