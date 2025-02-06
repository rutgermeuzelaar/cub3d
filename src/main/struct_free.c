/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:13:05 by nleusden          #+#    #+#             */
/*   Updated: 2025/02/06 17:10:25 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "map.h"
#include "player.h"
#include "cub3d.h"
#include "utilities.h"

static void	cheese(void *param)
{
	mlx_texture_t	*texture;

	texture = (mlx_texture_t *)param;
	mlx_delete_texture(texture);
}

int	arr_free_xl(void **arr, void (*free_func)(void *))
{
	int	i;

	i = 0;
	if (!arr)
		return (ERROR);
	while (arr[i])
	{
		free_func(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
	return (SUCCESS);
}

void	free_function(t_game *game)
{
	free(game->file_content);
	arr_free((void **)game->map.map);
	mlx_terminate(game->mlx);
	free(game->player.rays);
	arr_free_xl((void **)game->textures, cheese);
	printf("free'd resources\n");
	return ;
}
