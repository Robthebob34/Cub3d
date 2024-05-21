/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robinheck <robinheck@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:11 by robinheck         #+#    #+#             */
/*   Updated: 2024/05/21 11:59:30 by robinheck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
//# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

//parsing
int parse_map(char *file);

//utils
int	ft_strlen(const char *s);
char	**ft_split(const char *s, char c);

#endif