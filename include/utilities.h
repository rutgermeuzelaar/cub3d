/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/01 20:41:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/01 21:30:19 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

void	free_pointer_array(void **array, const int size);
int		arr_free(char **arr);
int		print_arr(char **arr);
char	*ft_strjoin2(char *s1, char const *s2);
int		skip_whitespaces(char *str);
int		ft_isspace(char c);
int		get_rgba(int color_hex, int alpha);
#endif
