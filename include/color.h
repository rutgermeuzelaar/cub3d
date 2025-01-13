/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 13:16:43 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/13 14:15:44 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include <stdint.h>
# ifdef __ORDER_LITTLE_ENDIAN__
typedef union u_color
{
	struct
	{
		unsigned char	alpha;
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
	}	s_bytes;
	int		rgb: 24;
	int32_t	rgba;
}	t_color;
# else
typedef union u_color
{
	struct
	{
		unsigned char	red;
		unsigned char	green;
		unsigned char	blue;
		unsigned char	alpha;
	}	s_bytes;
	int		rgb: 24;
	int32_t	rgba;
}	t_color;
# endif
#endif
