/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:11 by robinheck         #+#    #+#             */
/*   Updated: 2024/05/30 16:08:59 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../inc/get_next_line.h"
# include "../libft/libft.h"

# define S_W 1024
# define S_H 512

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
	char	orientation;
	double	player_x;
	double	player_y;
	t_map 	*map;
	int		mapX;
	int		mapY;
	double	cameraX ; //x-coordinate in camera space
    double	rayDirX;
    double	rayDirY;
	double	dir_x;
	double	dir_y;
	int		stepX;
	int		stepY;
	int		side; //was a NS or a EW wall hit?
	int		hit; //was there a wall hit?
	double	planeX;
	double	planeY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		s_w;
	int		s_h;
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