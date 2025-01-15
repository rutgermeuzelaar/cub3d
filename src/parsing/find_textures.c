/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/06 15:59:46 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/14 20:53:56 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utilities.h"

int	found_texture_prefix(char *str)
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

int	assign_texture(mlx_texture_t *texture, char *str)
{
	int	i;
	int	size;
	char	*texture_path;
	int		texture_index;

	(void)texture_index;
	texture_index = found_texture_prefix(str);
	i = (skip_whitespaces(str + 2) + 2);
	size = i;
	while (str[size] && !ft_isspace(str[size]))
		size++;
	size -= i;
	texture_path =  ft_substr(str, i, size);
	texture = mlx_load_png(texture_path);
	if (!texture)
		return (printf("havent found texture mb gang, take this gmod texture\n"), ERROR);
	return (SUCCESS);
}

int	texture_parsing(t_game *game)
{
	char	**file;
	int		i;
	int		j;
	int		i2;
	mlx_texture_t *textures;

	textures = (mlx_texture_t *)ft_calloc(5, sizeof(mlx_texture_t));
	if (!textures)
		return (SYS_ERROR);
	i = 0;
	j = 0;
	i2 = 0;
	file = game->map.map;
	printf("file begin = %s\n", game->map.map[0]);
	while (file[i])
	{
		j = skip_whitespaces(file[i]);
		if (file[i][j] && found_texture_prefix(file[i] + j) && &textures[i2])
		{
			//index the textures arr
			if (assign_texture(&textures[i2], file[i] + j) != SUCCESS)
			{
				textures[i2] = *mlx_load_png("textures/gmod.png");
				if (!&textures[i2])
					return (ERROR);
			}
			printf("found texture\n");
			i2++;
		}
		i++;
	}
	return (SUCCESS);
}
