/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:18:14 by nleusden          #+#    #+#             */
/*   Updated: 2025/02/10 13:16:26 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utilities.h"
#include "libft.h"

int	comma_condition(char *str, int *i, int *comma)
{
	if (str[*i] == ',' && str[*i + 1] == ',')
		return (1);
	else if (str[*i] == ',')
	{
		(*comma)++;
		(*i)++;
	}
	return (0);
}

int	loop_colors(char *str, int *i, int *num)
{
	int	count;

	count = 0;
	if (!ft_isdigit(str[*i]))
		return (1);
	(*num)++;
	while (str[*i] && ft_isdigit(str[*i]))
	{
		(*i)++;
		count++;
	}
	if (count > 3 || count == 0)
		return (1);
	return (0);
}

int	loop_color_format(char *str, int i)
{
	int	comma;
	int	num;

	comma = 0;
	num = 0;
	if (!ft_isdigit(str[i]))
		return (1);
	while (str[i] && !ft_isspace(str[i]))
	{
		if (loop_colors(str, &i, &num) == 1)
			return (1);
		if (comma_condition(str, &i, &comma) == 1)
			return (1);
	}
	if (comma != 2 || num != 3)
		return (1);
	return (0);
}

int	check_color_formatting(char *str, int *i)
{
	int	i2;

	i2 = 0;
	if (ft_strncmp(str + *i, "F", 1) == 0 || ft_strncmp(str + *i, "C", 1) == 0)
		(*i) += 1;
	else
		return (1);
	i2 += ((*i) + 1);
	while (str[i2] && str[i2] == ' ')
		i2++;
	if (loop_color_format(str, i2) != 0)
		return (-1);
	return (0);
}
