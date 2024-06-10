/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:11 by robinheck         #+#    #+#             */
/*   Updated: 2024/06/10 15:43:21 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>
# include "../libft/libft.h"

# define S_W 1024
# define S_H 512
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define ROT_SPEED 0.3
# define MOV_SPEED 0.5


typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_img;

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
	t_img	*w_image;
	void	*F;
	void	*C;
	int		*NO;
	int		*SO;
	int		*EA;
	int		*WE;
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
	double	rotSpeed;
	double	moveSpeed;
	int		s_w;
	int		s_h;
	t_img	db_img;
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