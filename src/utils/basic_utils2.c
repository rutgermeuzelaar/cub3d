/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:42:11 by rmeuzela          #+#    #+#             */
/*   Updated: 2025/01/14 12:12:03 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utilities.h"

void	free_pointer_array(void **array, const int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	get_rgba(int color_hex, int alpha)
{
	return (color_hex << 8 | alpha);	
}

int	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

char	**ft_arrndup(char **arr, size_t size)
{
	char	**ret;
	size_t		i;

	i = 0;
	ret = (char **)ft_calloc((size + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (arr[i] && i < size)
	{
		ret[i] = ft_strdup(arr[i]);
		if (!ret[i])
			return (arr_free(ret), NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}