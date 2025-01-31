/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pre_parse_colors.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 17:18:14 by nleusden      #+#    #+#                 */
/*   Updated: 2025/01/31 18:51:11 by rmeuzela      ########   odam.nl         */
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
		return (0);
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
		return (printf("not a digit\n"), 1);
	while (str[i] && !ft_isspace(str[i]))
	{
		if (loop_colors(str, &i, &num) == 1)
			return (printf("color problemo\n"), 1);
		if (comma_condition(str, &i, &comma) == 1)
			return (printf("2 commas in a row\n"), 1);
	}
	if (comma != 2 || num != 3)
		return (printf("incorrect nums = %d /commas = %d\n", num, comma), 1);
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
