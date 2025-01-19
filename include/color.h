/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 13:16:43 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/19 14:56:53 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include <stdint.h>
# ifdef __ORDER_LITTLE_ENDIAN__

typedef struct s_bytes
{
	uint8_t	alpha;
	uint8_t	blue;
	uint8_t	green;
	uint8_t	red;
}	t_bytes;
# else

typedef struct s_bytes
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;
}	t_bytes;
# endif

typedef union u_color
{
	t_bytes			bytes;				
	unsigned int	rgb: 24;
	uint32_t		rgba;
}	t_color;
#endif
