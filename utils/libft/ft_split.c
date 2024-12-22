/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:41:20 by nleusden          #+#    #+#             */
/*   Updated: 2023/11/01 14:15:14 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Allocates (with malloc(3)) and returns an array
// of strings obtained by splitting ’s’ using the
// character ’c’ as a delimiter. The array must end
// with a NULL pointer.

size_t	length(const char *s, char c)
{
	size_t	size;

	size = 0;
	while (s[size] && s[size] != c)
	{
		size++;
	}
	return (size);
}

/*
  length() starts with declaring size_t size

  this will be used to keep track of how long the index size isnt equal to c
  
  it returns the size back to splitall
*/

static void	ft_free(char **s2, int i)
{
	while (i > 0)
	{
		free(s2[i - 1]);
		i--;
	}
	free(s2);
}

/*
  ft_free() starts by freeing everything inside of the array
  it does this by decrementing i - 1 to skip the null terminator

  then it also frees the entire array
*/

static int	countwords(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && (s[i] != c))
			{
				i++;
			}
		}
		if (s[i] == c && s[i])
			i++;
	}
	return (count);
}
/*
  countwords starts by defining and declaring int count and int i

  count will be used to keep track of the amount of words
  i will be the index of where the string is

  it checks if s[i] isnt the split character and keep looping if so
  until it finds that it is equal to split character again

  when its done looping it returns count
*/

static char	**splitall(const char *s, char c, int x)
{
	int		i;
	int		j;
	size_t	size;
	char	**s2;

	i = 0;
	j = 0;
	s2 = (char **)ft_calloc((x + 1), sizeof(char *));
	if (s2 == NULL)
		return (NULL);
	while (x > i)
	{
		while (s[j] == c)
			j++;
		size = length(s + j, c);
		s2[i] = ft_substr(s, j, size);
		if (s2[i] == NULL)
		{
			ft_free(s2, i);
			return (NULL);
		}
		i++;
		j += size;
	}
	return (s2);
}

/*
  splitall starts with defclaring all variables
  
  defining i, j and calloc the array of strings s2
  it uses x (amount of words) + 1 to add space for a null terminator
  
  if allocation fails s2 returns NULL
  
  i is the index for the array s2
  j is the index for the string s
  
  size is using function length() (line 20)
  length finds te length of the string for the array
  
  after that a substring is made for the array with the size
  if the array is NULL, ft_free the entire array and strings inside,
  ft_free() = line(40)
  after that return NULL
  
  increment i to loop through array until max words are reached
  and j += size to skip through the wordlength

  return(s2) returns the array
*/

char	**ft_split(char const *s, char c)
{
	char	**s2;
	int		x;

	if (!s)
		return (NULL);
	x = countwords(s, c);
	s2 = splitall(s, c, x);
	if (s2 == NULL)
		return (NULL);
	return (s2);
}

/*
  split starts by making a double pointer array and int x
  
  first I check if s isnt empty
  
  then x = countwords() which finds the amount of words (go to line 57)
  
  after x has gotten the value of words s2 = splitall() (go to line 91)
  
  splitall returns the array of strings and is null terminated
  
  if S2 returns NULL, NULL is returned
  
  otherwise s2 is returned


*/