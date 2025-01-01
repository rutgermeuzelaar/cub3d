/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basic_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/01 20:42:11 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/01 21:30:09 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
