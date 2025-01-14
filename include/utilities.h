/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleusden <nleusden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:41:32 by rmeuzela          #+#    #+#             */
/*   Updated: 2025/01/14 15:35:20 by nleusden         ###   ########.fr       */
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
int		arrlen(char **arr);
char	*check_folder(char *a, char *b);
char	*file_check(char *file, char *format);
char	**ft_arrndup(char **arr, size_t size);
int		find_all_prefix(char *str);



#endif
