/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:56:44 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/22 16:29:55 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "libft.h"

int	check_surrounding(char **map, int y, int x)
{
	if (y == 0 || y == (arrlen(map) - 1))
		return (printf("\n-1\n"), ERROR);
	else if (x == 0 || (size_t)x == ft_strlen(map[y] - 1))
		return (printf("\n-1\n"), ERROR);
	if (ft_strchr("10NSEW", map[y - 1][x]) == NULL)
		return (printf("\n1\n"), ERROR);
	if (ft_strchr("10NSEW", map[y + 1][x]) == NULL)
		return (printf("\n2\n"), ERROR);
	if (ft_strchr("10NSEW", map[y][x - 1]) == NULL)
		return (printf("\n3\n"), ERROR);
	if (ft_strchr("10NSEW", map[y][x + 1]) == NULL)
		return (printf("\n4\n"), ERROR);
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
		i++;
	}
	return (SUCCESS);
}

char	**assign_prefixes(void)
{
	char	**ret;

	ret = (char **)ft_calloc(6, sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = "NO";
	ret[1] = "SO";
	ret[2] = "WE";
	ret[3] = "EA";
	ret[4] = "F";
	ret[5] = "C";
	ret[6] = NULL;
	return (ret);
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
