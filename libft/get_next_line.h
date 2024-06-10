/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:22:22 by rheck             #+#    #+#             */
/*   Updated: 2024/05/22 12:05:29 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

size_t	ft_strlen_gnl(char *str);
char	*get_next_line(int fd);
char	*ft_readed_line(char *src);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_move_start(char *start);
char	*ft_strjoin_gnl(char *start, char *buff);
char	*ft_join_gnl(char *dest, char *s1, char *s2);
int		ft_str_bf_new_line(char *str);

#endif