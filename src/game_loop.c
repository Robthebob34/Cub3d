/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:04:29 by rheck             #+#    #+#             */
/*   Updated: 2024/06/11 15:27:02 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int game_loop(void *d) // game loop
{
    t_db	*db;
	int		color;
	
    db = d;
    for (int x = 0; x < S_W; x++)
    {
        // calculate ray position and direction
        db->cameraX = 2 * x / (double)S_W - 1; // x-coordinate in camera space
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

    	double wallX; //where exactly the wall was hit
    	if (db->side == 0)
        	wallX = db->player_y + db->perpWallDist * db->rayDirY;
    	else 
    		wallX = db->player_x + db->perpWallDist * db->rayDirX;
      
    	wallX -= floor((wallX));
    	int texX = wallX * (double)db->db_img.size;

		if(db->side == 0 && db->rayDirX < 0)
        	texX = db->db_img.size - texX - 1;
    	if(db->side == 1 && db->rayDirY > 0)
        	texX = db->db_img.size - texX - 1;

        int lineHeight = (int)(S_H / db->perpWallDist);
        int drawStart = -lineHeight / 2 + S_H / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + S_H / 2;
        if (drawEnd >= S_H)
            drawEnd = S_H - 1;
        double step = 1.0 * db->db_img.size / lineHeight;
        double texPos = (drawStart - S_H / 2 + lineHeight / 2) * step;
		for(int j = 0; j < drawStart; j++)
		{
			set_image_pixel(db->w_image, x, j, 3071725);
		}
        for(int y = drawStart; y<drawEnd; y++)
        {
           int texY = (int)texPos & (db->db_img.size - 1);
           texPos += step;
			if (db->side == 1 && db->rayDirY < 0)
        		color = db->NO[db->db_img.size * texY + texX];
			else if (db->side == 1 && db->rayDirY > 0)
        		color = db->SO[db->db_img.size * texY + texX];
			else if (db->side == 0 && db->rayDirX < 0)
        		color = db->WE[db->db_img.size * texY + texX];
			else if (db->side == 0 && db->rayDirX > 0)
        		color = db->EA[db->db_img.size * texY + texX];
			set_image_pixel(db->w_image, x, y, color);
    	}
		for(int j = drawEnd; j < S_H; j++)
		{
			set_image_pixel(db->w_image, x, j, 2382603);
		}
    }
	mlx_put_image_to_window(db->mlx, db->win, db->w_image->img, 0, 0);
    return (0);
}