/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:11:19 by nleusden      #+#    #+#                 */
/*   Updated: 2025/02/13 16:19:30 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
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
# include "player.h"
# include "map.h"
# include "color.h"
# include "terminate.h"

typedef struct s_game
{
	char			*file_content;
	t_map			map;
	t_color			floor;
	t_color			ceiling;
	mlx_texture_t	**textures;
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	mlx_image_t		*debug;
	t_player		player;
}	t_game;

bool			init_game(t_game *const game, const char *map_name, \
				t_termination *termination);
void			draw_routine(void *param);

//parsing
char			*get_next_line(int fd);
int				fc_parsing(t_game *game);
int				parsing(t_game *game, const char *arg);
void			parsing_free(t_game *game);
void			pre_parsing_free(t_game *game);
int				texture_parsing(t_game *game);
int				get_file_contents(t_game *game_s, const char *str);
int				find_fd(const char *str, char *folder, char *format);
int				map_dimensions(t_game *game);
int				get_map(t_game *game);
int				find_all_prefix(const char *str, int *i);
void			free_function(t_game *game);
mlx_texture_t	*error_texture(void);
#endif
