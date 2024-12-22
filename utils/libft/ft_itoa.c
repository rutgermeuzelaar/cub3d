/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:18:36 by nleusden          #+#    #+#             */
/*   Updated: 2023/11/01 14:43:16 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//The atoi() function converts the initial portion of the string
//pointed to by nptr to int.

static int	get_len(int n)
{
	int	len;

	len = 1;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

/*
  get_len starts with declaring int len as 1
  this is done to also account for 1 digit numbers
  
  then if n divided by 10 isnt 0 
  itll increment len and divide by 10

  eventually once its accounted for every digit it returns len
*/

char	*create_string(int len, long nb, int negative)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > negative)
	{
		len--;
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}

/*
  create_string declares *str for the string its supposed to return
  after that ill malloc str with len + 1 to account for null terminator

  if str is NULL return NULL for failures

  str[len] null terminates the string right away
  
  as long as len is bigger than 1 or 0 depending on if negative
  
  decrement len and module of 10 + 48 to get the ascii value
  then divide by 10 to get the next int
  
  if the value is negative itll put a '-' at the start

  return the string
*/

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	int		negative;

	if (n == 0)
		return (create_string(1, 0, 0));
	len = get_len(n);
	nb = n;
	negative = 0;
	if (nb < 0)
	{
		negative = 1;
		nb = -nb;
		len++;
	}
	return (create_string(len, nb, negative));
}

/*
  ft_itoa starts by declaring 3 variables

  if the n is zero itll still create a string and return that string
  
  len = get_len() (line 18)

  nb = n so it can check for large numbers and negatives

  if nb is negative, the variable negative will be set to 1
  nb will become positive
  the length will be one larger to hold the '-'
  
  after that itll return create_string() see line 41
*/