/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:55:28 by robinheck         #+#    #+#             */
/*   Updated: 2024/06/10 16:36:14 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


u_int32_t	buffer[S_H][S_W];
void	drawVerLine(t_db *db, int x, int drawStart, int drawEnd, int color);
void   image_init(t_db *db, char *path);
void	drawframeLine(t_db *db);
void	set_image_pixel(t_img *image, int x, int y, int color);

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
            // Check if ray has hit a wall
            if (db->map->map[db->mapY][db->mapX] && db->map->map[db->mapY][db->mapX] == '1')
                db->hit = 1;
        }

        if (db->side == 0)
            db->perpWallDist = (db->sideDistX - db->deltaDistX);
        else
            db->perpWallDist = (db->sideDistY - db->deltaDistY);

        //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (db->side == 0)
        wallX = db->player_y + db->perpWallDist * db->rayDirY;
      else 
        wallX = db->player_x + db->perpWallDist * db->rayDirX;
      
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)wallX * (double)db->db_img.size;
      if(db->side == 0 && db->rayDirX < 0)
        texX = db->db_img.size - texX - 1;
      if(db->side == 1 && db->rayDirY > 0)
        texX = db->db_img.size - texX - 1;

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
        //int color = 22222222;//randomcolor();

        // give x and y sides different brightness
        // if (db->side == 1)
        //     color = color / 2;

        // draw the pixels of the stripe as a vertical line
        double step = 1.0 * db->db_img.size / lineHeight;
		//printf("step value : %f\n", step);
     //  Starting texture coordinate
        double texPos = (drawStart - S_H / 2 + lineHeight / 2) * step;
		for(int j = 0; j < drawStart; j++)
		{
			set_image_pixel(db->w_image, x, j, 3071725);
		}
        for(int y = drawStart; y<drawEnd; y++)
        {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
           int texY = (int)texPos & (db->db_img.size - 1);
		   //printf("texpos value : %f\n",texPos);
           texPos += step;
           int color = db->NO[db->db_img.size * texY + texX];
           // make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            // if(db->side == 1)
            //      color = (color >> 1) & 8355711;
			// if (db->side == 1)
            // 	color = color / 2;
            buffer[y][x] = color;
			//if (color > 0)
			set_image_pixel(db->w_image, x, y, color);
    	}
		for(int j = drawEnd; j < S_H; j++)
		{
			set_image_pixel(db->w_image, x, j, 2382603);
		}
        //drawVerLine(db, x, drawStart, drawEnd, 1646844);
    }
	mlx_put_image_to_window(db->mlx, db->win, db->w_image->img, 0, 0);
	
    return (0);
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

void	drawVerLine(t_db *db, int x, int drawStart, int drawEnd, int color)
{
	int	i;
    int j = 0;
	(void)color;
	i = drawStart;
    while(j < i)
    {
        mlx_pixel_put(db->mlx, db->win, x, j, 3071725);
        j++;
    }
	while (i <= drawEnd)
	{
		mlx_pixel_put(db->mlx, db->win, x, i, buffer[i][x]);
		i++;		
	}
    while (drawEnd < S_H)
    {
        mlx_pixel_put(db->mlx, db->win, x, drawEnd, 2382603);
        drawEnd++;
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
        if(db->map->map[(int)(db->player_y)][(int)(db->player_x + db->dir_x * db->moveSpeed)] != '1')
            db->player_x += db->dir_x * db->moveSpeed;
        if(db->map->map[(int)(db->player_y + db->dir_y * db->moveSpeed)][(int)(db->player_x)] != '1')
            db->player_y += db->dir_y * db->moveSpeed;
	}
	if (keycode == S)
	{
		if(db->map->map[(int)(db->player_y)][(int)(db->player_x - db->dir_x * db->moveSpeed)] != '1')
            db->player_x -= db->dir_x * db->moveSpeed;
        if(db->map->map[(int)(db->player_y - db->dir_y * db->moveSpeed)][(int)(db->player_x)] != '1')
            db->player_y -= db->dir_y * db->moveSpeed;
    }
	return (0);
}

static int	*xpm_to_img(t_db *data, char *path)
{
	int		*buffer;
	int		x;
	int		y;

	image_init(data, path);
	buffer = malloc(sizeof(int) * (data->db_img.size * data->db_img.size));
	y = 0;
	while (y < data->db_img.size)
	{
		x = 0;
		while (x < data->db_img.size)
		{
			buffer[y * data->db_img.size + x]
				= data->db_img.addr[y * data->db_img.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, data->db_img.img);
    // for (int i = 0; i < data->db_img.size * data->db_img.size; i ++)
    //     printf("%d\n", buffer[i]);
	return (buffer);
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;
	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	init_textures(t_db *data)
{
	data->NO = xpm_to_img(data, data->path_north);
	data->SO = xpm_to_img(data, data->path_north);
	data->EA = xpm_to_img(data, data->path_north);
	data->WE = xpm_to_img(data, data->path_north);
}

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 512;
	img->endian = 0;
}
void	init_img(t_db *data)
{
	
	data->w_image->img = mlx_new_image(data->mlx, S_W, S_H);
	if (data->w_image == NULL)
		printf("tkt pour plus tard");
	data->w_image->addr = (int *)mlx_get_data_addr(data->w_image->img, &data->w_image->pixel_bits,
			&data->w_image->size_line, &data->w_image->endian);
	printf("init : %p\n", data->w_image->addr);
	return ;
}

void   image_init(t_db *db, char *path)
{
    db->db_img.img = mlx_xpm_file_to_image(db->mlx, path, &db->db_img.size, &db->db_img.size);
    if(!db->db_img.img)
        return;
    db->db_img.addr = (int *)mlx_get_data_addr(db->db_img.img, &db->db_img.pixel_bits,
	    &db->db_img.size_line, &db->db_img.endian);
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
    printf("path : %s\n", db->path_north);
    init_textures(db);
	init_img_clean(db->w_image);
	init_img(db);
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