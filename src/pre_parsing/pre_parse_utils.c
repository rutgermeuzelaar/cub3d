/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:56:44 by nleusden          #+#    #+#             */
/*   Updated: 2025/02/10 13:26:29 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utilities.h"
#include "libft.h"

int	check_surrounding(char **map, int y, int x)
{
	if (y == 0 || y == (arrlen(map) - 1))
		return (ERROR);
	else if (x == 0 || (size_t)x == (ft_strlen(map[y]) - 1))
		return (ERROR);
	if (map[y - 1][x] == '\0' || ft_strchr("10NSEW", map[y - 1][x]) == NULL)
		return (ERROR);
	if (map[y + 1][x] == '\0' || ft_strchr("10NSEW", map[y + 1][x]) == NULL)
		return (ERROR);
	if (map[y][x - 1] == '\0' || ft_strchr("10NSEW", map[y][x - 1]) == NULL)
		return (ERROR);
	if (map[y][x + 1] == '\0' || ft_strchr("10NSEW", map[y][x + 1]) == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	check_double_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] && str[i + 1] == '\n')
			return (ERROR);
		else if (str[i] == '\n' && str[i + 1] == '\0')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	*assign_intarr(void)
{
	int	*ret;
	int	i;

	i = 0;
	ret = (int *)ft_calloc(6, sizeof(int));
	if (!ret)
		return (NULL);
	while (ret[i] && i < 6)
	{
		ret[i] = 0;
		i++;
	}
	return (ret);
}
