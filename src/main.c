/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:55:28 by robinheck         #+#    #+#             */
/*   Updated: 2024/06/13 17:37:24 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_image(t_db *db, int x)
{
	int	j;

	j = 0;
	while (j < db->draw_start)
	{
		set_image_pixel(db->w_image, x, j, db->c_color);
		j++;
	}
	while (j < db->draw_end)
	{
		draw_wall(db, x, j);
		j++;
	}
	while (j < S_H)
	{
		set_image_pixel(db->w_image, x, j, db->f_color);
		j++;
	}
}

void	draw_frame_line(t_db *db)
{
	int	x;
	int	y;

	x = 0;
	while (x < S_W)
	{
		y = 0;
		while (y < S_H)
		{
			mlx_pixel_put(db->mlx, db->win, x, y, db->buffer[y][x]);
			y++;
		}
		x++;
	}
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	play(t_db *db)
{
	set_player_position(db);
	init_textures(db);
	mlx_start(db);
	init_img_clean(db->w_image);
	init_img(db);
	mlx_hook(db->win, 17, 0, destroy_window, NULL);
	mlx_hook(db->win, 2, 0, &key_hook, db);
	mlx_loop_hook(db->mlx, &game_loop, db);
	mlx_loop(db->mlx);
}

int	main(int argc, char **argv)
{
	t_db	*db;

	db = malloc(sizeof(t_db));
	if (!db)
		return (1);
	db->map = malloc(sizeof(t_map));
	db->w_image = malloc (sizeof(t_img));
	if (!db->map || !db->w_image)
		exit_free(db, "Error\nMalloc error");
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
	play(db);
	exit_end(db, "finito papito\n");
	return (0);
}
