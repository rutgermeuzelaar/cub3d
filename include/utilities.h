/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nleusden <nleusden@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/01 20:41:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/02/13 16:34:31 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# if defined(_WIN32)
#  define OS_NAME "windows"
#  define OS_COMPATIBLE 1
# elif defined(__linux__)
#  define OS_NAME "linux"
#  define OS_COMPATIBLE 1
# else
#  define OS_NAME "unknown"
#  define OS_COMPATIBLE 0
# endif

# include <unistd.h>

typedef enum e_mini_error
{
	SYS_ERROR = -1,
	SUCCESS = 0,
	ERROR = 1,
}	t_mini_error;

void	free_pointer_array(void **array, const int size);
int		arr_free(void **arr);
int		print_arr(char **arr);
char	*ft_strjoin2(char *s1, char const *s2);
int		skip_whitespaces(const char *str);
int		ft_isspace(char c);
int		get_rgba(int color_hex, int alpha);
int		arrlen(char **arr);
char	*check_folder(const char *a, const char *b);
char	*file_check(char *file, char *format);
char	**ft_arrndup(char **arr, size_t size);
int		check_os_compatibility(void);
int		check_color_formatting(const char *str, int *i);
int		check_map_format(const char *str, const size_t start);
int		*assign_intarr(void);
char	**assign_prefixes(void);
int		check_double_newline(const char *str, const size_t start);
int		check_surrounding(char **map, int y, int x);
char	*change_crlf_to_lf(char *str);
int		arr_free_xl(void **arr, void (*free_func)(void *));

#endif
