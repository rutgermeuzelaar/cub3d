/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_pad.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/07 15:01:57 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/07 20:30:09 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "player.h"
#include "map.h"
#include "minimap.h"

static size_t	get_padding(const size_t axis_length)
{
	const size_t	minimap_size = TILE_OFFSET * 2;
	size_t			padding;

	if (axis_length >= minimap_size)
	{
		return (0);
	}
	padding = minimap_size - axis_length;
	if (padding % 2 != 0)
	{
		padding++;
	}
	return (padding);
}

static void	set_padded_map(t_map *map, const size_t x_padding, \
			const size_t y_padding, char **padded_map)
{
	const size_t	y_padding_half = y_padding / 2;
	const size_t	x_padding_half = x_padding / 2;
	char			*map_string;
	size_t			i;

	i = 0;
	while (i < y_padding_half)
	{
		i++;
	}
	while (i < map->height - y_padding_half)
	{
		map_string = map->map[i - y_padding_half];
		ft_memcpy(padded_map[i] + x_padding_half, map_string, \
		ft_strlen(map_string));
		i++;
	}
	free_pointer_array((void **)map->map, map->height - y_padding);
	map->map = padded_map;
	map->player_x += x_padding_half;
	map->player_y += y_padding_half;
}

static bool	create_padded_map(t_map *map)
{
	const size_t	x_padding = get_padding(map->width);
	const size_t	y_padding = get_padding(map->height);
	char			**padded_map;
	size_t			i;

	i = 0;
	map->height += y_padding;
	map->width += x_padding;
	padded_map = ft_calloc(map->height + 1, sizeof(char *));
	if (!padded_map)
		return (false);
	while (i < map->height)
	{
		padded_map[i] = ft_calloc(map->width + 1, sizeof(char));
		if (!padded_map[i])
		{
			free_pointer_array((void **)padded_map, i);
			return (false);
		}
		ft_memset(padded_map[i], EMPTY_TILE, map->width);
		i++;
	}
	set_padded_map(map, x_padding, y_padding, padded_map);
	return (true);
}

bool	pad_map(t_map *map)
{
	const size_t	map_min_size = TILE_OFFSET * 2;

	if (map->height >= map_min_size && map->width >= map_min_size)
	{
		return (true);
	}
	return (create_padded_map(map));
}
