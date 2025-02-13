/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nilsleusden@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:59:46 by nleusden          #+#    #+#             */
/*   Updated: 2025/02/13 23:19:40 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "map.h"
#include "libft.h"
#include "cub3d.h"
#include "utilities.h"

static int	found_texture_prefix(char *str)
{
	if (str[0] == '\0')
		return (0);
	if (ft_strncmp(str, "NO", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "SO", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "WE", 2) == 0)
		return (3);
	else if (ft_strncmp(str, "EA", 2) == 0)
		return (4);
	return (0);
}

static mlx_texture_t	*error_texture(void)
{
	mlx_texture_t	*ret;

	ret = mlx_load_png("textures/test/gmod.png");
	if (!ret)
		return (NULL);
	return (ret);
}

static int	assign_texture(mlx_texture_t **texture, char *str)
{
	int		i;
	int		size;
	char	*texture_path;
	int		texture_index;

	(void)texture_index;
	texture_index = found_texture_prefix(str);
	i = (skip_whitespaces(str + 2) + 2);
	size = i;
	while (str[size] && !ft_isspace(str[size]))
		size++;
	size -= i;
	texture_path = ft_substr(str, i, size);
	if (!texture_path)
		return (printf("Error allocation\n"), SYS_ERROR);
	*texture = mlx_load_png(texture_path);
	if (!*texture)
	{
		*texture = error_texture();
		if (!*texture)
			return (printf("Error Textures\n"), free(texture_path), SYS_ERROR);
	}
	return (free(texture_path), SUCCESS);
}

int	texture_parsing(t_game *game)
{
	char			**file;
	int				i;
	int				j;
	int				i2;

	game->textures = ft_calloc((4 + 1), sizeof(mlx_texture_t *));
	if (!game->textures)
		return (SYS_ERROR);
	i = 0;
	i2 = 0;
	file = game->map.map;
	while (file[i] && i2 < 6)
	{
		j = skip_whitespaces(file[i]);
		if (file[i][j] && found_texture_prefix(file[i] + j))
		{
			if (assign_texture(&game->textures[i2], file[i] + j) != SUCCESS)
				return (arr_free((void **)game->textures), ERROR);
			i2++;
		}
		i++;
	}
	return (SUCCESS);
}
