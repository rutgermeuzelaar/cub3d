/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nilsleusden@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:11:19 by nleusden          #+#    #+#             */
/*   Updated: 2024/12/22 15:41:10 by nleusden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "../utils/MLX42/include/MLX42/MLX42.h"
# include "../utils/libft/libft.h"
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
	char			**map;
	int				*res;
	mlx_texture_t	*textures;
}					t_game;

// main processing
int		main(int argc, char **argv);

//parsing
char	*get_next_line(int fd);
int		check_file(char *str, t_game *game_s);


//textures applying

//player movement

//utils
int		arr_free(char **arr);
int		print_arr(char **arr);
char	*ft_strjoin2(char *s1, char const *s2);
int		skip_whitespaces(char *str);
int		ft_isspace(char c);



# endif