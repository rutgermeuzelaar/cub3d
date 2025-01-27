/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:29:58 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/22 15:57:11 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	loop_prefixes(char **prefixes, char *str, int *index)
{
	int	i;

	i = 0;
	while (prefixes[i])
	{
		if (ft_strncmp(prefixes[i], str, ft_strlen(prefixes[i])) == 0)
		{
			if (index != NULL && ft_strlen(prefixes[i]) == 2)
				(*index) += ft_strlen(prefixes[i]);
			return (i);
		}
		i++;
	}
	return (-1);
}

int	check_for_input(char **prefixes, char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] != '\n')
	{
		if (str[*i] == '\f' || str[*i] == '\r'
			|| str[*i] == '\t' || str[*i] == '\v')
			return (printf("found invalid whitespaces (could be windows file format issue)\n"), 1);
		else if (str[*i] == ' ')
		{
			(*i) += skip_whitespaces(str + *i);
			return (printf("end of filepath\n"), 0);
		}
		(*i)++;
	}
	if (str[*i] && str[*i] == '\n' && str[*i + 1] && !ft_isspace(str[*i + 1])
		&& loop_prefixes(prefixes, str + *i + 1, NULL) < 0)
		return (printf("died at after newline == prefix or space\n"), 1);
	return (0);
}

int	one_of_each(int *arr, char **prefix_arr, char *str, int *i)
{
	int	ret;

	ret = 0;
	if (*arr == 1)
		return (printf("already encountered prefix\n"), 1);
	*arr = 1;
	if (check_color_formatting(str, i) < 0)
		return (printf("color checking error\n"), 1);
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '\f' || str[*i] == '\n'
		|| str[*i] == '\r' || str[*i] == '\t' || str[*i] == '\v')
		return (printf("invalid whitespace found or no texture\n"), 1);
	ret = check_for_input(prefix_arr, str, i);
	if (ret != 0)
		return (printf("prototype function input found wrongdoing %d\n\n'%s'\n", ret, str + *i), 1);
	return (0);
}

int	find_all_prefix(char *str, int *i)
{
	char	**prefixes;
	int		ret;
	int		*track;

	ret = 0;
	track = assign_intarr();
	if (!track)
		return (-1);
	prefixes = assign_prefixes();
	if (!prefixes)
		return (free(track), -1);
	*i += skip_whitespaces(str);
	while (str[*i])
	{
		ret = loop_prefixes(prefixes, str + *i, i);
		if (ret >= 0 && one_of_each(track + ret, prefixes, str, i))
			return (1);
		if (all_prefixes_found(track) == 0)
			return (printf("found all prefixes\n"), 0);
		(*i)++;
	}
	return (printf("didnt find every prefix && reached end of str\n"), 1);
}
