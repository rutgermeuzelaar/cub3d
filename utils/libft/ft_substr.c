/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:11:09 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:21:58 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates (with malloc(3)) and returns a substring
// from the string ’s’.
// The substring begins at index ’start’ and is of
// maximum size ’len’.

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (s == NULL || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (0);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

/*
  ft_substr starts with declaring 2 variables

  then s is checked if NULL
  and start is checked if its longer than string length s
  if so, itll return a stringduplicate of ""

  if the start + len is bigger than the length of strlen(s)
  it takes the length and changes it to strlen(s) - start position
  this is to ensure not too much is malloc'd
  
  sub dynamically allocated with malloc
  to hold the len + 1 so its null terminated

  after this sub is checked for allocation failure
  if it does fail return NULL

  while the index i is smaller than the len
  the sub will be filled with s[start + i]
  this is to ensure you start at the substring in s

  in the end sub is null terminated
  and sub is returned
*/