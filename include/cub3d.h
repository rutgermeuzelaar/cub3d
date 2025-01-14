/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:11:19 by nleusden          #+#    #+#             */
/*   Updated: 2025/01/14 11:23:03 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1280
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 720
# endif
# include "MLX42/MLX42.h"
# include "libft.h"
# include "player.h"
# include "map.h"
# include "color.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_mini_error
{
	SYS_ERROR = -1,
	SUCCESS = 0,
	ERROR = 1,
}	t_mini_error;

typedef struct		s_game
{
	char			*file_content;
	t_map			map;
	t_color			floor;
	t_color			ceiling;
	int				*res;
	mlx_texture_t	*textures;
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	mlx_image_t		*debug;
	t_player		player;
}					t_game;

bool	init_game(t_game *const game);
// main processing
// int		main(int argc, char **argv);

//parsing
char	*get_next_line(int fd);
int		fc_parsing(t_game *game);
int		parsing(t_game *game, char *arg);
int		texture_parsing(t_game *game);
int		get_file_contents(t_game *game_s, char *str);
int		find_fd(char *str, char *folder, char *format);

//textures applying

//player movement
# endif
