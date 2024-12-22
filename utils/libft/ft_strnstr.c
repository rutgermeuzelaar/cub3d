/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:25:17 by nleusden          #+#    #+#             */
/*   Updated: 2023/11/01 14:13:06 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strnstr() function locates the first	occurrence of the  null-termi-
// nated  string little in the string big, where not more than len charac-
// ters are	searched.  Characters that appear after	a `\0'	character  are
// not  searched.

void	changer(int *x, int *j, size_t *len)
{
	*x -= *j - 1;
	*len += *j - 1;
	*j = 0;
}

/*
  x value is where in big you are

  x -= j - 1 is done to go back to where you started finding equals
  but ofcourse - 1 because you want to check one further this time
  
  len will also have the same effect 
  
  and j is reset to 0 because you want to check little from the start
*/

void	looper(int *x, int *j, size_t *len)
{
	*j += 1;
	*x += 1;
	*len -= 1;
}

/*
  j is being incremented by one (these functions are to save space)
  x is being incremented by one
  len is being decremented by one
*/

void	looper2(int *x, int *j, size_t *len)
{
	*x += 1;
	*len -= 1;
	*j -= *j;
}

/*
  x is being incremented by one (these functions are used to save space)
  len is being decremented by one
  j is being decremented by j to reset it
*/

char	*finder(const char *big, const char *little, size_t len)
{
	int	x;
	int	j;
	int	start;

	x = 0;
	j = 0;
	start = 0;
	while (big[x] && little[j] && len > 0)
	{
		if (big[x] == little[j])
		{
			start = x;
			while (big[x] && little[j] && big[x] == little[j] && len > 0)
				looper(&x, &j, &len);
			if (little[j] == '\0')
				return ((char *)big + start);
			else
				changer(&x, &j, &len);
		}
		else
			looper2(&x, &j, &len);
	}
	return (NULL);
}

/*
  finder starts by declaring 3 variables

  x and j are index's and start is used to reset if j isnt finished
  j is for little
  x is for big
  
  if x is equal to j, start becomes x
  
  then while it keeps being the same looper() line 38
  
  if little reaches a null terminator it returns big + start
  which just means how far in the string little is found

  else changer() see line 20

  and if big isnt the same as little looper2() see line 51
  
  if little isnt found in big it returns NULL
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big2;

	if (*little == '\0')
		return ((char *)big);
	else
		big2 = finder(big, little, len);
	return (big2);
}

/*
  ft_strnstr starts by declaring string big2

  if little is empty return big
  
  else big2 = finder() see line 64
  return big2
*/