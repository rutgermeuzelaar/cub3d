/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:46:56 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/22 16:35:12 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "libft.h"

char	*ft_strjoin2(char *s1, char const *s2)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = (char *)ft_calloc(1, sizeof(char));
		s1[0] = '\0';
	}
	dst = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
		dst[i++] = s2[j++];
	free(s1);
	dst[i] = '\0';
	return (dst);
}

int	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	return (i);
}

int	arr_free(void **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (ERROR);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
	return (SUCCESS);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	skip_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
	{
		i++;
	}
	return (i);
}
