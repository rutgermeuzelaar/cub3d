/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nilsleusden@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:13:18 by nleusden      #+#    #+#                 */
/*   Updated: 2024/12/27 19:54:30 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "MLX42/MLX42.h"
#include "map.h"
#include "minimap.h"
#include "libft.h"
#include "drawing.h"

// int	main(int argc, char **argv)
// {
// 	t_game	*game_struct;

// 	if (argc != 2 && argv[1] == NULL)
// 		return (ERROR);
// 	game_struct = ft_calloc(2, sizeof(t_game));
// 	if (!game_struct)
// 		return (ERROR);
// 	if (check_file(argv[1], game_struct) == SUCCESS)
// 	{
// 		print_arr(game_struct->map);
// 		return (SUCCESS);
// 	}
// 	return (ERROR);
// }

// https://github.com/codam-coding-college/MLX42/blob/master/docs/Colors.md
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	main(void)
{
	mlx_t	*mlx;
	mlx_image_t	*minimap;
	t_map	map;
	const char *cheese[] = {
		"111111",
		"100101",
		"101001",
		"1100N1",
		"111111"
	};
	size_t i;

	i = 0;
	mlx = mlx_init(wINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!mlx)
	{
		return (EXIT_FAILURE);
	}
	map.height = 5;
	map.width = 6;
	map.map = malloc(sizeof(char *) * map.height);
	if (!map.map)
	{
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	while (i < map.height)
	{
		map.map[i] = ft_strdup(cheese[i]);
		if (!map.map[i])
		{
			while (i != 0)
			{
				free(map.map[i]);
				i--;
			}
			free(map.map);
			mlx_terminate(mlx);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	minimap = mlx_new_image(mlx, map.width * TILE_SIZE, map.height * TILE_SIZE);\
	if (!minimap)
	{
		return (EXIT_FAILURE);
	}
	ft_memset(minimap->pixels, 255, minimap->width * minimap->height * BPP);
	draw_minimap(&map, minimap);
	mlx_image_to_window(mlx, minimap, 100, 300);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
