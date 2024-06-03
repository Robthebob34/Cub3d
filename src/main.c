/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:55:28 by robinheck         #+#    #+#             */
/*   Updated: 2024/06/03 15:08:28 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	drawVerLine(t_db *db, int x, int drawStart, int drawEnd, int color);

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
unsigned int randomcolor()
{
    // Initialiser le générateur de nombres aléatoires avec le temps actuel
    //srand(time(NULL));

    // Générer des composantes rouge, verte et bleue aléatoires
    unsigned char rouge = rand() % 256;
    unsigned char vert = rand() % 256;
    unsigned char bleu = rand() % 256;
	// rouge = 20;
	// vert = 40;
	// bleu = 100;
    // Combiner les composantes en un seul entier RGB
    unsigned int couleur = (rouge << 16) | (vert << 8) | bleu;

    return couleur;
}

int game_loop(void *d) // game loop
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
			 //calculate step and initial sideDist
			if (db->rayDirX < 0)
			{
				db->stepX = -1;
				db->sideDistX = (db->player_x - db->mapX) * db->deltaDistX;
			}
			else
			{
				db->stepX = 1;
				db->sideDistX = (db->mapX + 1.0 - db->player_x) * db->deltaDistX;
			}
			if (db->rayDirY < 0)
			{
				db->stepY = -1;
				db->sideDistY = (db->player_y - db->mapY) * db->deltaDistY;
			}
			else
			{
				db->stepY = 1;
				db->sideDistY = (db->mapY + 1.0 - db->player_y) * db->deltaDistY;
			}
			while (db->hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (db->sideDistX < db->sideDistY)
				{
					db->sideDistX += db->deltaDistX;
					db->mapX += db->stepX;
					db->side = 0;
				}
				else
				{
					db->sideDistY += db->deltaDistY;
					db->mapY += db->stepY;
					db->side = 1;
				}
				//Check if ray has hit a wall
				if (db->map->map[db->mapX][db->mapY] > 0) 
					db->hit = 1;
    		}
			if(db->side == 0) 
				db->perpWallDist = (db->sideDistX - db->deltaDistX);
      		else
				db->perpWallDist = (db->sideDistY - db->deltaDistY);
			//Calculate height of line to draw on screen
			int h = db->mapY + (1 - db->stepY) / 2;
      		int lineHeight = (int)(h / db->perpWallDist);

      		//calculate lowest and highest pixel to fill in current stripe
      		int drawStart = -lineHeight / 2 + h / 2;
     		if(drawStart < 0)
				drawStart = 0;
     		int drawEnd = lineHeight / 2 + h / 2;
      		if(drawEnd >= h)
				drawEnd = h - 1;
			int color = randomcolor();

      		//give x and y sides different brightness
      		if (db->side == 1) 
				color = color / 2;

      		//draw the pixels of the stripe as a vertical line
      		drawVerLine(db, x, drawStart, drawEnd, color);
		}
		return(0);
	}

void	drawVerLine(t_db *db, int x, int drawStart, int drawEnd, int color)
{
	int i = drawStart;

	while (i <= drawEnd)
	{
		mlx_pixel_put(db->mlx, db->win, i, x,color);
		i++;		
	}
}

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
    while (y < (start_y + side_length))
    {
        x = start_x;
        while (x < (start_x + side_length))
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
				draw_ray(db, j * 120 + 56, i * 120 + 56, 20, 0xea3131); // changer 20 -> 5 et 60 -> 56
			}
			j++;
		}
		i++;
		
	}
}
int	user_input(int keycode, t_db *db)
{
	(void)keycode;
	(void)db;
	return(0);
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
	mlx_key_hook(db->win, user_input, db);
	//display_map(db);
	mlx_loop_hook(db->mlx, &game_loop, db); // game loop continuously call a specified function to update the game state and render the frames.
	//mlx_key_hook(db->mlx, &mlx_key, &db); // key press and release
	mlx_loop(db->mlx); // mlx loop
	return (0);
}