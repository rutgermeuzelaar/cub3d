/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pre_parse_map.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 13:51:11 by nleusden      #+#    #+#                 */
/*   Updated: 2025/02/13 16:53:19 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utilities.h"
#include "libft.h"

static int	check_double_player(const char *str, const size_t start)
{
	int	i;
	int	playercount;

	i = start;
	playercount = 0;
	while (str[i])
	{
		if (ft_strchr("NSEW", str[i]) != NULL)
			playercount++;
		if (playercount > 1)
			return (ERROR);
		i++;
	}
	if (playercount < 1)
		return (ERROR);
	return (SUCCESS);
}

static int	check_unwanted_chars(const char *str, const size_t start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (ft_strchr("10\n NSEW", str[i]) == NULL)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	check_closed_map(const char *map, const size_t start)
{
	char	**arr_map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr_map = ft_split(map + start, '\n');
	if (!arr_map)
		return (SYS_ERROR);
	while (arr_map[i])
	{
		j = 0;
		while (arr_map[i][j])
		{
			if (ft_strchr("0NSWE", arr_map[i][j]) != NULL)
			{
				if (check_surrounding(arr_map, i, j) != SUCCESS)
					return (arr_free((void **)arr_map), ERROR);
			}
			j++;
		}
		i++;
	}
	arr_free((void **)arr_map);
	return (SUCCESS);
}

static int	pre_parse_map(const char *map, const size_t start)
{
	if (check_double_newline(map, start) != SUCCESS)
		return (printf("Error found double newline in map\n"), ERROR);
	if (check_unwanted_chars(map, start) != SUCCESS)
		return (printf("Error found unwanted char in map\n"), ERROR);
	if (check_double_player(map, start) != SUCCESS)
		return (printf("Error invalid player amount\n"), ERROR);
	if (check_closed_map(map, start) != SUCCESS)
		return (printf("Error map isnt closed\n"), ERROR);
	return (SUCCESS);
}

int	check_map_format(const char *str, const size_t start)
{
	int	i;
	int	ret;

	i = start;
	ret = 0;
	while (str[i] && str[i] != '1' && str[i] != ' ' && str[i] != '0')
		i++;
	if (str[i] == '\0')
		return (printf("Error map doesnt exist\n"), ERROR);
	else if (str[i - 1] != '\n')
		return (printf("Error invalid char before map\n"), ERROR);
	ret = pre_parse_map(str, i);
	if (ret != SUCCESS)
		return (ERROR);
	return (ret);
}
