/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:11 by robinheck         #+#    #+#             */
/*   Updated: 2024/05/28 17:43:44 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../inc/get_next_line.h"
# include "../libft/libft.h"

typedef struct s_map
{
	char	**map;
	char	**texture_path;
	char	*rgb_f;
	char	*rgb_c;
}				t_map;

typedef struct s_db
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*F;
	void	*C;
	void	*NO;
	void	*SO;
	void	*EA;
	void	*WE;
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	char	*floor_color;
	char	*cieling_color;
	double	player_x;
	double	player_y;
	t_map 	*map;
}				t_db;


//parsing
int 	parse_map(char *file, t_db *db);
char 	*ft_read_line( char **file);
int		check_texture(t_db *db);
char	**get_map(char **file);
int		is_rounded(t_db *db, int x, int y);
int		verfiy_characters(t_db *db);

//window events
int		destroy_window(t_db *data);

//player
void	set_player_position(t_db *db);

#endif