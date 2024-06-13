/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:08:12 by rheck             #+#    #+#             */
/*   Updated: 2024/06/13 14:11:53 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_color(t_db *db, int j, int i)
{
	int color = i * (db->w_image->size_line / 4) + j;
	return(db->w_image->addr[color]);
}

int	fade_color(int color, int data_color, double fade)
{
	int src_r = (color >> 16) & 0xFF;
    int src_g = (color >> 8) & 0xFF;
    int src_b = color & 0xFF;

    int dest_r = (data_color >> 16) & 0xFF;
    int dest_g = (data_color >> 8) & 0xFF;
    int dest_b = data_color & 0xFF;

    int r = (int)((1 - fade) * dest_r + fade * src_r);
    int g = (int)((1 - fade) * dest_g + fade * src_g);
    int b = (int)((1 - fade) * dest_b + fade * src_b);

    return (r << 16) | (g << 8) | b;
}
void	draw_square(t_db *db, int x, int y, int color, int size)
{
	int i = x;
	int j = y;
	int h = 0;
	int w = 0;
	while(h < size - 1)
	{
		w = 0;
		j = y;
		while(w < size - 1)
		{
			mlx_pixel_put(db->mlx, db->win, j, i, fade_color(color, get_color(db, j, i), 0.25));
			w++;
			j++;
		}
		h++;
		i++;
	}
}
void	draw_player_point(t_db *db, int x, int y, int color, int size)
{
	int i = x;
	int j = y;
	int h = 0;
	int w = 0;
	while(h < size - 1)
	{
		w = 0;
		j = y;
		while(w < size - 1)
		{
			mlx_pixel_put(db->mlx, db->win, j, i, fade_color(color, get_color(db, j, i), 0.9));
			w++;
			j++;
		}
		h++;
		i++;
	}
}
void	draw_minimap(t_db *db)
{
	int pos_x = floor(db->player_x) - 1;
	int y = floor(db->player_y);
	int i = 0;
	int j = 0;
	while(i < 3)
	{
		j = 0;
		int pos_y = y - 1;
		while(j < 3)
		{
			if(db->map->map[pos_y][pos_x] == '1')
				draw_square(db, i * 50, j * 50, 00000, 50);
			if(db->map->map[pos_y][pos_x] == '0' || db->map->map[pos_y][pos_x] == 'N')
				draw_square(db, i * 50, j * 50, 16777215, 50);
			j++;
			pos_y++;
		}
		i++;
		pos_x++;
	}
	draw_player_point(db, 70, 70, 16711680, 5);
}
