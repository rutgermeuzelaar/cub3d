/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:29:58 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/14 15:36:49 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "libft.h"

// char **assign_prefixes(void)
// {
// 	char	**ret;

// 	ret = (char **)ft_calloc(6, sizeof(char *));
// 	if (!ret)
// 		return (NULL);
// 	ret[0] = "NO";
// 	ret[1] = "SO";
// 	ret[2] = "WE";
// 	ret[3] = "EA";
// 	ret[4] = "F";
// 	ret[5] = "C";
// 	ret[6] = NULL;
// 	return (ret);
// }

// int	*assign_intarr(void)
// {
// 	int	*ret;
// 	int	i;

// 	i = 0;
// 	ret = (int *)ft_calloc(6, sizeof(int));
// 	if (!ret)
// 		return (NULL);
// 	while (ret[i])
// 	{
// 		ret[i] = 0;
// 		i++;
// 	}
// 	return (ret);
// }

// int	loop_prefixes(char **prefixes, char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (prefixes[i])
// 	{
// 		if (ft_strncmp(prefixes[i], str, 2) == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// int	one_of_each(int *arr, char **prefix_arr, char *str, int *i)
// {
// 	int	ret;

// 	ret = 0;
// 	if (arr[0] == 1)
// 		return (1);
// 	else if (arr[0] == 0)
// 		arr[0] = 1;
// 	while (str[*i] && str[*i] == ' ')
// 		(*i)++;
// 	if (str[*i] == '\f' || str[*i] == '\n'
// 		|| str[*i] == '\r' || str[*i] == '\t' || str[*i] == '\v')
// 		return (1);
// 	ret = check_for_input(str, i);
// 	if (ret != 0)
// 		return (1);
// 	return (0);
// }

// int	find_all_prefix(char *str)
// {
// 	int	i;
// 	char	**prefixes;
// 	int	ret;
// 	int	*track;

// 	ret = 0;
// 	track = assign_intarr();
// 	if (!ret)
// 		return (-1);
// 	prefixes = assign_prefixes();
// 	if (!prefixes)
// 		return (free(track), -1);
// 	i = skip_whitespaces(str);
// 	while (str[i])
// 	{
// 		ret = loop_prefixes(prefixes, str + i);
// 		if (ret > 0 && one_of_each(track + ret, prefixes, str + i, &i))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
