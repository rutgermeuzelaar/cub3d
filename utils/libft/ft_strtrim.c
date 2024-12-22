/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:27:39 by nleusden          #+#    #+#             */
/*   Updated: 2023/11/01 14:14:10 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates (with malloc(3)) and returns a copy of
// ’s1’ with the characters specified in ’set’ removed
// from the beginning and the end of the string.

char	*allocate(const char *s1, size_t trimlength, size_t start)
{
	char	*str;

	str = (char *)malloc(trimlength + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + start, trimlength + 1);
	return (str);
}

/*
  allocate() starts with declaring str as a string

  after that str is malloced with trimlength + 1
  this is to account for the null terminator

  if the allocation fails and str == NULL
  it returns NULL

  if not it uses my strlcpy to copy my s1 + start with trimlength + 1
  to str

  and it returns str
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	trimlength;

	start = 0;
	end = ft_strlen(s1);
	if (s1 == 0)
		return (0);
	if (set == 0)
		return (ft_strdup(s1));
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
	{
		if (s1[end] == s1[start])
		{
			end = ft_strlen(s1);
			break ;
		}
		end--;
	}
	trimlength = end - start;
	str = allocate(s1, trimlength, start);
	return (str);
}

/*
  ft_strtrim starts by declaring 4 variables

  we have start and end for the starting and end point

  if s1 is 0 itll return 0

  if set is 0 itll return a string duplicate of s1

  I use my own strchr to find the first occurance of set (man strchr)
  by using a while loop and incrementing start

  then the next while loop loops until it finds where start ended
  and it goes backwards using strchr to find the first occurance again

  if it finds that end is equal to start
  end will be the string length of s1 because nothing was found
  and the while loops is exited
  
  the trimlength is the end - start
  then str = allocate() see line 19

  returns str after
*/