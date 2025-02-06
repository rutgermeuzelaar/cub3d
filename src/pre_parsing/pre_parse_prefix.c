/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:29:58 by nleusden          #+#    #+#             */
/*   Updated: 2025/02/06 17:50:53 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "libft.h"

int	all_prefixes_found(int *arr)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (arr[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_prefix(const char *str, int *index)
{
	const char	*cheese[7] = {
		"NO",
		"SO",
		"WE",
		"EA",
		"F",
		"C",
		0
	};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(str, cheese[i], ft_strlen(cheese[i])) == 0)
		{
			if (index != NULL && ft_strlen(cheese[i]) == 2)
				(*index) += ft_strlen(cheese[i]);
			return (i);
		}
		i++;
	}
	return (-1);
}

int	check_for_input(char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] != '\n')
	{
		if (ft_strchr("\f\r\t\v", str[*i]) != NULL)
			return (printf("Error invalid whitespace\n"), 1);
		else if (str[*i] == ' ')
		{
			(*i) += skip_whitespaces(str + *i);
			return (0);
		}
		(*i)++;
	}
	if (str[*i] && str[*i] == '\n' && str[*i + 1] && !ft_isspace(str[*i + 1])
		&& is_prefix(str + *i + 1, NULL) < 0)
		return (printf("died at after newline == prefix or space\n"), 1);
	return (0);
}

int	one_of_each(int *arr, char *str, int *i)
{
	int	ret;

	ret = 0;
	if (*arr == 1)
		return (printf("Error duplicate prefix\n"), 1);
	*arr = 1;
	if (check_color_formatting(str, i) < 0)
		return (printf("Error color format\n"), 1);
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '\f' || str[*i] == '\n'
		|| str[*i] == '\r' || str[*i] == '\t' || str[*i] == '\v')
		return (printf("invalid whitespace found or no texture\n"), 1);
	ret = check_for_input(str, i);
	if (ret != 0)
		return (printf("prototype function input found wrong doing\n"), 1);
	return (0);
}

int	find_all_prefix(char *str, int *i)
{
	int		ret;
	int		*track;

	ret = 0;
	track = assign_intarr();
	if (!track)
		return (-1);
	*i += skip_whitespaces(str);
	while (str[*i])
	{
		ret = is_prefix(str + *i, i);
		if (ret >= 0 && one_of_each(track + ret, str, i))
			return (free(track), ERROR);
		else if (ret < 0)
			return (free(track), ERROR);
		if (all_prefixes_found(track) == 0)
			return (free(track), SUCCESS);
		(*i)++;
		(*i) += skip_whitespaces(str + *i);
	}
	free(track);
	return (printf("Error prefixes not found\n"), 1);
}
