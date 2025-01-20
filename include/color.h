/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 13:16:43 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/20 13:26:22 by rmeuzela      ########   odam.nl         */
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

// Credits to raylib: https://www.raylib.com/cheatsheet/cheatsheet.html
# define LIGHTGRAY  (uint32_t)(200 << 24 | 200 << 16 | 200 << 8 | 255)
# define GRAY       (uint32_t)(130 << 24 | 130 << 16 | 130 << 8 | 255)
# define DARKGRAY   (uint32_t)(80 << 24 | 80 << 16 | 80 << 8 | 255)
# define YELLOW     (uint32_t)(253 << 24 | 249 << 16 | 0 << 8 | 255)
# define GOLD       (uint32_t)(255 << 24 | 203 << 16 | 0 << 8 | 255)
# define ORANGE     (uint32_t)(255 << 24 | 161 << 16 | 0 << 8 | 255)
# define PINK		(uint32_t)(255 << 24 | 109 << 16 | 194 << 8 | 255)
# define RED        (uint32_t)(230 << 24 | 41 << 16 | 55 << 8 | 255)
# define MAROON     (uint32_t)(190 << 24 | 33 << 16 | 55 << 8 | 255)
# define GREEN      (uint32_t)(0 << 24 | 228 << 16 | 48 << 8 | 255)
# define LIME       (uint32_t)(0 << 24 | 158 << 16 | 47 << 8 | 255)
# define DARKGREEN  (uint32_t)(0 << 24 | 117 << 16 | 44 << 8 | 255)
# define SKYBLUE    (uint32_t)(102 << 24 | 191 << 16 | 255 << 8 | 255)
# define BLUE       (uint32_t)(0 << 24 | 121 << 16 | 241 << 8 | 255)
# define DARKBLUE   (uint32_t)(0 << 24 | 82 << 16 | 172 << 8 | 255)
# define PURPLE     (uint32_t)(200 << 24 | 122 << 16 | 255 << 8 | 255)
# define VIOLET     (uint32_t)(135 << 24 | 60 << 16 | 190 << 8 | 255)
# define DARKPURPLE (uint32_t)(112 << 24 | 31 << 16 | 126 << 8 | 255)
# define BEIGE      (uint32_t)(211 << 24 | 176 << 16 | 131 << 8 | 255)
# define BROWN      (uint32_t)(127 << 24 | 106 << 16 | 79 << 8 | 255)
# define DARKBROWN  (uint32_t)(76 << 24 | 63 << 16 | 47 << 8 | 255)

# define WHITE      (uint32_t)(255 << 24 | 255 << 16 | 255 << 8 | 255)
# define BLACK      (uint32_t)(0 << 24 | 0 << 16 | 0 << 8 | 255)
# define BLANK    	(uint32_t)(0 << 24 | 0 << 16 | 0 << 8 | 0)
# define MAGENTA    (uint32_t)(255 << 24 | 0 << 16 | 255 << 8 | 255)

#endif
