/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:55:28 by robinheck         #+#    #+#             */
/*   Updated: 2024/06/05 16:40:59 by rheck            ###   ########.fr       */
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
   
    db->planeX = 0.66;
    db->planeY = 0; //the 2d raycaster version of camera plane

    db->s_w = S_W;
    db->dir_x = 0;
    db->dir_y = -1;
	db->rotSpeed = ROT_SPEED;
    db->moveSpeed = MOV_SPEED;
}
unsigned int randomcolor()
{
    // Initialiser le générateur de nombres aléatoires avec le temps actuel
    srand(time(NULL));

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
    mlx_clear_window(db->mlx, db->win);
    for (int x = 0; x < S_W; x++)
    {
        // calculate ray position and direction
        db->cameraX = 2 * x / (double)db->s_w - 1; // x-coordinate in camera space
        db->rayDirX = db->dir_x + db->planeX * db->cameraX;
        db->rayDirY = db->dir_y + db->planeY * db->cameraX;
        db->deltaDistX = fabs(1 / db->rayDirX);
        db->deltaDistY = fabs(1 / db->rayDirY);

        // Debug: Print ray position and direction
        //printf("x: %d, cameraX: %f, rayDirX: %f, rayDirY: %f, deltaDistX: %f, deltaDistY: %f\n",
        //       x, db->cameraX, db->rayDirX, db->rayDirY, db->deltaDistX, db->deltaDistY);

        // which box of the map we're in
        db->mapX = (int)db->player_x;
        db->mapY = (int)db->player_y;

        // length of ray from one x or y-side to next x or y-side
		db->deltaDistX = sqrt(1 + (db->rayDirY * db->rayDirY) / (db->rayDirX * db->rayDirX));
		db->deltaDistY = sqrt(1 + (db->rayDirX * db->rayDirX) / (db->rayDirY * db->rayDirY));
        db->hit = 0; // was there a wall hit?

        // calculate step and initial sideDist
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

        // Debug: Print step and initial sideDist
       // printf("stepX: %d, stepY: %d, sideDistX: %f, sideDistY: %f\n",
              // db->stepX, db->stepY, db->sideDistX, db->sideDistY);

        while (db->hit == 0)
        {
            // jump to next map square, either in x-direction, or in y-direction
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
            //printf("x: %d, cameraX: %f, rayDirX: %f, rayDirY: %f, deltaDistX: %f, deltaDistY: %f\n",
             //  x, db->cameraX, db->rayDirX, db->rayDirY, db->deltaDistX, db->deltaDistY);
           // printf("stepX: %d, stepY: %d, sideDistX: %f, sideDistY: %f\n",
            //   db->stepX, db->stepY, db->sideDistX, db->sideDistY);
            //printf("mapX: %d, mapY: %d, hit: %d, side: %d\n", db->mapX, db->mapY, db->hit, db->side);

            // Check if ray has hit a wall
            if (db->map->map[db->mapY][db->mapX] && db->map->map[db->mapY][db->mapX] == '1')
                db->hit = 1;
        }

        // Debug: Print map position and hit information

        if (db->side == 0)
            db->perpWallDist = (db->sideDistX - db->deltaDistX);
        else
            db->perpWallDist = (db->sideDistY - db->deltaDistY);

        // Calculate height of line to draw on screen
        //int h = db->mapY + (1 - db->stepY) / 2;
        int lineHeight = (int)(S_H / db->perpWallDist);
        // calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + S_H / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + S_H / 2;
        if (drawEnd >= S_H)
            drawEnd = S_H - 1;
        int color = randomcolor();

        // give x and y sides different brightness
        if (db->side == 1)
            color = color / 2;

        // Debug: Print drawing parameters
        //printf("x: %d, drawStart: %d, drawEnd: %d, color: %d peperwall_dist : %f\n\n\n", x, drawStart, drawEnd, color , db->perpWallDist);

        // draw the pixels of the stripe as a vertical line
        drawVerLine(db, x, drawStart, drawEnd, color);
    }
    return (0);
}




void	drawVerLine(t_db *db, int x, int drawStart, int drawEnd, int color)
{
	int	i;
	
	i = drawStart;
	while (i <= drawEnd)
	{
		mlx_pixel_put(db->mlx, db->win, x, i,color);
		i++;		
	}
}


int	user_input(int keycode, t_db *db)
{
	(void)keycode;
	(void)db;
	return(0);
}

int	key_hook(int keycode, t_db *db)
{
    if (keycode == ESC)
	{
		
		//free_data(data);
		exit(EXIT_SUCCESS);
	}
	if (keycode == D)
	{
      double oldDirX = db->dir_x;
      db->dir_x = db->dir_x * cos(db->rotSpeed) - db->dir_y * sin(db->rotSpeed);
      db->dir_y = oldDirX * sin(db->rotSpeed) + db->dir_y * cos(db->rotSpeed);
      double oldPlaneX = db->planeX;
      db->planeX = db->planeX * cos(db->rotSpeed) - db->planeY * sin(db->rotSpeed);
      db->planeY = oldPlaneX * sin(db->rotSpeed) + db->planeY * cos(db->rotSpeed);
	}
	if (keycode == A)
	{
      double oldDirX = db->dir_x;
      db->dir_x = db->dir_x * cos(-db->rotSpeed) - db->dir_y * sin(-db->rotSpeed);
      db->dir_y = oldDirX * sin(-db->rotSpeed) + db->dir_y * cos(-db->rotSpeed);
      double oldPlaneX = db->planeX;
      db->planeX = db->planeX * cos(-db->rotSpeed) - db->planeY * sin(-db->rotSpeed);
      db->planeY = oldPlaneX * sin(-db->rotSpeed) + db->planeY * cos(-db->rotSpeed);
	}
	if (keycode == W)
	{
         printf("BEFORE player pos y: %f\n", db->player_y);
        printf("BEFOREplayer pos x: %f\n", db->player_x);
        if(db->map->map[(int)(db->player_y)][(int)(db->player_x + db->dir_x * db->moveSpeed)] != '1')
            db->player_x += db->dir_x * db->moveSpeed;

            
        if(db->map->map[(int)(db->player_y + db->dir_y * db->moveSpeed)][(int)(db->player_x)] != '1')
            db->player_y += db->dir_y * db->moveSpeed;
        printf("AFTER player pos y: %f\n", db->player_y);
        printf("AFTER pos x: %f\n", db->player_x);
	}
	if (keycode == S)
	{
        printf("BEFORE player pos y: %f\n", db->player_y);
        printf("BEFOREplayer pos x: %f\n", db->player_x);
		if(db->map->map[(int)(db->player_y)][(int)(db->player_x - db->dir_x * db->moveSpeed)] != '1')
            db->player_x -= db->dir_x * db->moveSpeed;
        if(db->map->map[(int)(db->player_y - db->dir_y * db->moveSpeed)][(int)(db->player_x)] != '1')
            db->player_y -= db->dir_y * db->moveSpeed;
         printf("AFTER player pos y: %f\n", db->player_y);
        printf("AFTER pos x: %f\n", db->player_x);
    }
	return (0);
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
	set_player_position(db);
	db->mlx = mlx_init();
	mlx_start(db);
	mlx_hook(db->win, 17, 0, destroy_window, NULL);
	mlx_key_hook(db->win, user_input, db);
	//display_map(db);
	printf("MAIN plane x : %f plane : y %f\n", db->planeX, db->planeY);
	mlx_hook(db->win, 2, 0,&key_hook, db); // key press and release
	mlx_loop_hook(db->mlx, &game_loop, db); // game loop continuously call a specified function to update the game state and render the frames.
	//mlx_hook(db->mlx, 03, 0,&key_hook, &db);
	mlx_loop(db->mlx); // mlx loop
	return (0);
}