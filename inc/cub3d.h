/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:11 by robinheck         #+#    #+#             */
/*   Updated: 2024/06/12 14:14:41 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>
# include "../libft/libft.h"

# define S_W 2048
# define S_H 1024
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define ROT_SPEED 0.25
# define MOV_SPEED 0.5

typedef struct s_img
{
	void			*img;
	int				*addr;
	int				pixel_bits;
	int				size_line;
	int				endian;
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
	double		f_r;
	double		f_g;
	double		f_b;
	double		c_r;
	double		c_g;
	double		c_b;
	int			c_color;
	int			f_color;
	void		*mlx;
	void		*win;
	void		*img;
	t_img		*w_image;
	void		*floor;
	void		*c;
	int			*no;
	int			*so;
	int			*ea;
	int			*we;
	char		*path_north;
	char		*path_south;
	char		*path_east;
	char		*path_west;
	char		*floor_color;
	char		*cieling_color;
	char		orientation;
	double		player_x;
	double		player_y;
	t_map		*map;
	int			map_x;
	int			map_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		dir_x;
	double		dir_y;
	int			step_x;
	int			step_y;
	int			side;
	int			hit;
	double		plane_x;
	double		plane_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		p_wall_dist;
	int			s_w;
	int			s_h;
	t_img		db_img;
	double		wall_x;
	int			tex_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		step;
	double		tex_pos;
	u_int32_t	buffer[S_H][S_W];
}				t_db;

int		rgb_to_int(int r, int g, int b);
int		parse_map(char *file, t_db *db);
char	*ft_read_line( char **file);
int		check_texture(t_db *db);
char	**get_map(char **file);
int		is_rounded(t_db *db, int x, int y);
int		verfiy_characters(t_db *db);
int		destroy_window(t_db *data);
void	image_init(t_db *db, char *path);
void	draw_frame_line(t_db *db);
void	set_image_pixel(t_img *image, int x, int y, int color);
void	init_textures(t_db *data);
void	set_player_position(t_db *db);
void	init_img_clean(t_img *img);
void	init_img(t_db *data);
void	image_init(t_db *db, char *path);
int		game_loop(void *d);
int		key_hook(int keycode, t_db *db);
void	mlx_start(t_db *db);
void	set_direction(t_db *db);
void	draw_image(t_db *db, int x);
void	set_direction_2(t_db *db);
void	initialise_tabs(char tab[6][6], int tab2[6]);
int		verify_texture(int j, int tab2[], int i, t_db *db);
void	load_texture(t_db *db, char *t_path);
void	draw_wall(t_db *db, int x, int j);
void	set_colors(t_db *db);

#endif