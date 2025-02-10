/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:51:11 by nleusden          #+#    #+#             */
/*   Updated: 2025/02/10 17:36:50 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utilities.h"
#include "libft.h"

int	check_double_player(char *str)
{
	int	i;
	int	playercount;

	i = 0;
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

int	check_unwanted_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("10\n NSEW", str[i]) == NULL)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	check_closed_map(char *map)
{
	char	**arr_map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr_map = ft_split(map, '\n');
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

int	pre_parse_map(char *map)
{
	int	i;

	i = 0;
	(void)i;
	if (check_double_newline(map) != SUCCESS)
		return (printf("Error found double newline in map\n"), ERROR);
	if (check_unwanted_chars(map) != SUCCESS)
		return (printf("Error found unwanted char in map\n"), ERROR);
	if (check_double_player(map) != SUCCESS)
		return (printf("Error invalid player amount\n"), ERROR);
	if (check_closed_map(map) != SUCCESS)
		return (printf("Error map isnt closed\n"), ERROR);
	return (SUCCESS);
}

int	check_map_format(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] && str[i] != '1' && str[i] != ' ' && str[i] != '0')
		i++;
	if (str[i] == '\0')
		return (printf("Error map doesnt exist\n"), ERROR);
	else if (str[i - 1] != '\n')
		return (printf("Error invalid char before map\n"), ERROR);
	ret = pre_parse_map(str + i);
	if (ret != SUCCESS)
		return (ERROR);
	return (ret);
}
