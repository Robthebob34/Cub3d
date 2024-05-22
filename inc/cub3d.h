/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:11 by robinheck         #+#    #+#             */
/*   Updated: 2024/05/22 13:19:11 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
//# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../inc/get_next_line.h"
# include "../libft/libft.h"

typedef struct s_map
{
	char	**map;
	char	**texture_path;
}				t_map;

typedef struct s_db
{
	void	*mlx;
	void	*win;
	void	*F;
	void	*C;
	void	*NO;
	void	*SO;
	void	*EA;
	void	*WE;
	t_map 	*map;
}				t_db;


//parsing
int 	parse_map(char *file, t_db *db);
char 	*ft_read_line( char **file);
int		load_texture(t_db *db);
char	**get_map(char **file);

#endif