/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:29:58 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/20 12:49:55 by nleusden         ###   ########.fr       */
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

int	loop_prefixes(char **prefixes, char *str, int *index)
{
	int	i;

	i = 0;
	while (prefixes[i])
	{
		if (ft_strncmp(prefixes[i], str, ft_strlen(prefixes[i])) == 0)
		{
			if (index != NULL)
				(*index) += ft_strlen(prefixes[i]);
			return (i);
		}
		i++;
	}
	return (-1);
}

// int	check_color_formatting(char *str, int i)
// {
// 	int	i2;

// 	i2 = i;
// 	if (ft_strncmp(str + i2, "F", 1) == 0 || ft_strncmp(str + i2, "C", 1) == 0)
// 		i2 += 1;
// 	else
// 		return (1);
// 	while (str[i2] && str[i2] == ' ')
// 		i2++;
// 	while (str[i2] && ft_isspace(str[i2]))
// 	{
// 		if (!ft_isdigit(str[i2]) && str[i2] != ',')
// 			return (-1);
// 		i2++;
// 	}
// 	return (0);
// }

int	check_for_input(char **prefixes, char *str, int *i)
{
	// if (check_color_formatting(str, *i) < 0)
	// 	return (1);
	while (str[*i] != '\0' && str[*i] != '\n')
	{
		if (str[*i] == '\f' || str[*i] == '\r'
			|| str[*i] == '\t' || str[*i] == '\v')
			return (1);
		else if (str[*i] == ' ')
		{
			(*i) += skip_whitespaces(str + *i);
			return (printf("end of filepath\n"), 0);
		}
		printf("%c", str[*i]);
		(*i)++;
	}
	printf("\n");
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
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '\f' || str[*i] == '\n'
		|| str[*i] == '\r' || str[*i] == '\t' || str[*i] == '\v')
		return (printf("invalid whitespace found or no texture\n"), 1);
	ret = check_for_input(prefix_arr, str, i);
	if (ret != 0)
		return (printf("prototype function input found wrongdoing\n"), 1);
	printf("sucessfully checked line\n");
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
	printf("i before loop = %d\n", *i);
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

// some problems with looping / indexing
// not sure how to fix this yet....