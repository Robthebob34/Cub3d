/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:55:28 by robinheck         #+#    #+#             */
/*   Updated: 2024/06/11 15:25:40 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

u_int32_t	buffer[S_H][S_W];

void	set_direction(t_db *db)
{
	if (db->orientation == 'N')
	{
		db->planeX = 0.66;
    	db->planeY = 0;
		db->dir_x = 0;
    	db->dir_y = -1;
	}
	else if (db->orientation == 'E')
	{
		db->planeX = 0;
    	db->planeY = 0.66;
		db->dir_x = 1;
    	db->dir_y = 0;
	}
	else if (db->orientation == 'S')
	{
		db->planeX = -0.66;
    	db->planeY = 0;
		db->dir_x = 0;
    	db->dir_y = 1;
	}
	else if (db->orientation == 'W')
	{
		db->planeX = 0;
    	db->planeY = -0.66;
		db->dir_x = -1;
    	db->dir_y = 0;
	}
}

void	mlx_start(t_db *db)
{
	if (!db->mlx)
	{
		exit(EXIT_FAILURE);
	}
	db->win = mlx_new_window(db->mlx, S_W, 
	 		 S_H, "cub3d");
	if (!db->win)
	{
		exit(EXIT_FAILURE);
	}
	set_direction(db);
}

void	drawframeLine(t_db *db)
{
	for(int x = 0; x < S_W; x++)
	{
		for(int y = 0; y < S_H; y++)
		{
			mlx_pixel_put(db->mlx, db->win, x, y, buffer[y][x]);
		}
	}
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;
	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

int main (int argc, char **argv)
{
	t_db	*db;
	
	db = malloc(sizeof(t_db));
	db->map = malloc(sizeof(t_map));
	db->w_image = malloc (sizeof(t_img));
	if (argc != 2)
	{
		printf("Usage Cub3d : ./cub3d map_name.cub");
		return (1);
	}
	if (!parse_map(argv[1], db))
	{
		printf("Error\n");
		return (1);
	}
	set_player_position(db);
	db->mlx = mlx_init();
	mlx_start(db);
    init_textures(db);
	init_img_clean(db->w_image);
	init_img(db);
	mlx_hook(db->win, 17, 0, destroy_window, NULL);
	mlx_hook(db->win, 2, 0,&key_hook, db);
	mlx_loop_hook(db->mlx, &game_loop, db);
	mlx_loop(db->mlx);
	printf("wtf\n");
	return (0);
}