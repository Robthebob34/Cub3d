/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:55:28 by robinheck         #+#    #+#             */
/*   Updated: 2024/05/30 16:09:51 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	
}

void game_loop(void *d) // game loop
	{
		t_db *db;

		db = d;
		for(int x = 0; x < S_W; x++)
		{
			//calculate ray position and direction
			db->cameraX = 2 * x / (double)db->s_w - 1; //x-coordinate in camera space
			db->rayDirX = db->dir_x + db->planeX * db->cameraX;
			db->rayDirY = db->dir_y + db->planeY * db->cameraX;
			db->deltaDistX = fabs(1 / db->rayDirX);
			db->deltaDistY = fabs(1 / db->rayDirY);

			//which box of the map we're in
			db->mapX = (int) db->player_x;
			db->mapY = (int) db->player_y;

			

			//length of ray from one x or y-side to next x or y-side
			db->deltaDistX = (db->rayDirX == 0) ? 1e30 : fabs(1 / db->rayDirX);
			db->deltaDistY = (db->rayDirY == 0) ? 1e30 : fabs(1 / db->rayDirY);
			db->hit = 0; //was there a wall hit?
		}
	}

// int	handle_events(int keycode, t_db *db)
// {

// 	if (keycode == ESC)
// 	{
// 		mlx_destroy_window(db->mlx, db->win);
// 		free_db(db);
// 		exit(EXIT_SUCCESS);
// 	}
// 	if (keycode == D)
// 		move->x = 1;
// 	if (keycode == S)
// 		move->y = 1;
// 	if (keycode == A)
// 		move->x = -1;
// 	if (keycode == W)
// 		move->y = -1;
// 	if (keycode == D || keycode == W || keycode == S || keycode == A)
// 		move_player(db, move);
// 	return (1);
// }

// void	mlx_events(t_db *db)
// {
// 	mlx_hook(db->win, 17, 0, destroy_window, NULL);
// 	mlx_hook(db->win, 2, 1L << 0, handle_events, db);
// 	mlx_loop(db->mlx);
// }

// void	draw_white(t_db *db, int x, int y)
// {
// 	int i = x;
// 	int j = y;
// 	while (x < i + 60)
// 	{
// 		int y = 0;
// 		while (y < j + 60)
// 		{
// 			mlx_pixel_put(db->mlx, db->win, x, y, 0x99999);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void draw_square(t_db *db, int start_x, int start_y, int side_length, int color)
{
    int x;
    int y;

    y = start_y;
    while (y < start_y + side_length - 2)
    {
        x = start_x;
        while (x < start_x + side_length - 2)
        {
            mlx_pixel_put(db->mlx, db->win, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_ray(t_db *db, int start_x, int start_y, int side_length, int color)
{
    int x;
    int y;

    y = start_y;
	if (db->orientation == 'N')
	{
		
	}
    while (y < start_y + side_length)
    {
        x = start_x;
        while (x < start_x + side_length)
        {
           mlx_pixel_put(db->mlx, db->win, x, y, color);
            x++;
        }
        y++;
    }
}

void	display_map(t_db *db)
{
	int	i;
	int	j;
	int y;
	int x;
	x = 0;
	y = 0;
	i = 0;
	j = 0;
	while (db->map->map[i])
	{
		j = 0;
		while (db->map->map[i][j])
		{
			if (db->map->map[i][j] == '1')
			{
				draw_square(db, j * 120, i * 120, 120, 0x6666666);
			}
			if (db->map->map[i][j] == '0')
			{
				draw_square(db, j * 120, i * 120, 120, 0xfffffff);
			}
			if (db->map->map[i][j] == 'N' || db->map->map[i][j] == 'E' || db->map->map[i][j] == 'W' || db->map->map[i][j] == 'S')
			{
				draw_square(db, j * 120, i * 120, 120, 0xfffffff);
				draw_square(db, j * 120 + 50, i * 120 + 50, 20, 0x93c47d);
				draw_ray(db, j * 120 + 60, i * 120 + 60, 20, 0xea3131);
			}
			j++;
		}
		i++;
		
	}
}

int main (int argc, char **argv)
{
	t_db	*db;
	
	db = malloc(sizeof(t_db));
	db->map = malloc(sizeof(t_map));
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
	db->mlx = mlx_init();
	mlx_start(db);
	mlx_hook(db->win, 17, 0, destroy_window, NULL);
	display_map(db);
	//mlx_loop_hook(db->mlx, (int)&game_loop, &db); // game loop continuously call a specified function to update the game state and render the frames.
	//mlx_key_hook(db->mlx, &mlx_key, &db); // key press and release
	mlx_loop(db->mlx); // mlx loop
	return (0);
}


