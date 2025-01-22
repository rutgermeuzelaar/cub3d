/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:51:11 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/22 13:59:43 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "libft.h"

int	pre_parse_map(char *map)
{
	int	i;

	i = 0;
	while(map[i])
		i++;
	return (SUCCESS);
}


int	check_map_format(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	// printf("remainder\n'%s'\n", str);
	while (str[i] && str[i] != '1' && str[i] != ' ' && str[i] != '0')
		i++;
	if (str[i] == '\0')
		return (printf("map parsing endfile error\n"), ERROR);
	else if (str[i - 1] != '\n')
		return (printf("character before map error\n"), ERROR);
	// printf("str = '%s'\n", str + i);
	ret = pre_parse_map(str + i);
	if (ret != SUCCESS)
		return (ERROR);
	return (ret);
}
