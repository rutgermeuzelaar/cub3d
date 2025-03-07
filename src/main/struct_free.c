/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:13:05 by nleusden          #+#    #+#             */
/*   Updated: 2025/03/07 12:42:24 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "map.h"
#include "player.h"
#include "cub3d.h"
#include "utilities.h"

static int	arr_free_xl(void **arr, void (*free_func)(void *))
{
	int	i;

	i = 0;
	if (!arr)
		return (ERROR);
	while (i < 5)
	{
		free_func(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
	return (SUCCESS);
}

static void	free_textures(void *param)
{
	mlx_texture_t	*texture;

	texture = (mlx_texture_t *)param;
	if (param == NULL)
		return ;
	mlx_delete_texture(texture);
}

void	pre_parsing_free(t_game *game)
{
	if (game->file_content)
		free(game->file_content);
	if (game->map.map)
		arr_free((void **)game->map.map);
	return ;
}

void	parsing_free(t_game *game)
{
	if (game->file_content)
		free(game->file_content);
	if (game->map.map)
		arr_free((void **)game->map.map);
	if (game->textures)
		arr_free_xl((void **)game->textures, free_textures);
	printf("free'd parsing\n");
	return ;
}
