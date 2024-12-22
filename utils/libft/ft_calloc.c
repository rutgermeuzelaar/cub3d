/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:56:02 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:23:02 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Upon successful completion with both nmemb and size non-zero
//calloc() shall return a pointer to the allocated space.

void	*ft_calloc(size_t nmemb, size_t size)
{
	long	totalsize;
	void	*ptr;

	if (size == 0 || nmemb == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	if (nmemb > 2147483647 || size > 2147483647)
		return (NULL);
	totalsize = (long)nmemb * (long)size;
	if (totalsize > 2147483647)
		return (NULL);
	ptr = malloc(totalsize);
	if (ptr != NULL)
	{
		ft_bzero(ptr, (size_t)totalsize);
	}
	return ((void *)ptr);
}

/*
  ft_calloc starts with declaring 2 variables

  it first checks if the parameters are 0
  
  if so it mallocs 0 to ptr
  and returns ptr

  then it checks if both parameters are bigger than INT_MAX
  if so it returns NULL

  the totalsize is the number membytes times size
  
  if the totalsize is bigger than INT_MAX it also returns NULL

  after that check it mallocs totalsize to ptr

  and if ptr isnt NULL
  itll use my ft_bzero() to set the malloced memory to \0

  returns a void pointer to that memory block (ptr)
*/