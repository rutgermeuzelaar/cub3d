/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_crlf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nilsleusden@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:17:29 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/27 00:40:00 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "libft.h"

static int	lf_file_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\r')
		{
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*change_CRLF_to_LF(char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = lf_file_len(str);
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\r' && str[i + 1] == '\n')
		{
			ret[j++] = '\n';
			i += 2;
		}
		else
			ret[j++] = str[i++];
	}
	ret[j] = '\0';
	return (ret);
}
