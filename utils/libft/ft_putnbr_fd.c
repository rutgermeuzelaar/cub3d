/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:42:00 by nleusden          #+#    #+#             */
/*   Updated: 2023/10/31 18:24:11 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Outputs the integer ’n’ to the given file
//descriptor.

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		ft_putchar_fd(n + 48, fd);
	}
}

/*
  this function uses recursion
  
  if the int n is INT_MIN
  itll create a special case with ft_putstr_fd
  
  if n is negative itll add a '-'
  and use recursion to go back to ft_putnbr_fd as a positive
  
  if n is bigger than 10 or the same as

  use recursion to divide and use module of 10
  until it isnt bigger than 10 anymore
  
  if all of these are passed itll use ft_putchar_fd
  n + 48 is to pass the ascii value 0 plus n 
  
  all of the recursion instances will be passed through it
  to complete the function
*/