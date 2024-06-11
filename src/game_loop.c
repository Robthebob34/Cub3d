/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:04:29 by rheck             #+#    #+#             */
/*   Updated: 2024/06/11 16:30:34 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_data(t_db *db, int x)
{
	db->cameraX = 2 * x / (double)S_W - 1;
	db->rayDirX = db->dir_x + db->planeX * db->cameraX;
	db->rayDirY = db->dir_y + db->planeY * db->cameraX;
	db->deltaDistX = fabs(1 / db->rayDirX);
	db->deltaDistY = fabs(1 / db->rayDirY);
	db->mapX = (int)db->player_x;
	db->mapY = (int)db->player_y;
	db->deltaDistX = sqrt(1 + (db->rayDirY * db->rayDirY) / (db->rayDirX * db->rayDirX));
	db->deltaDistY = sqrt(1 + (db->rayDirX * db->rayDirX) / (db->rayDirY * db->rayDirY));
	db->hit = 0;
}

void	calculate_step_sidedist(t_db *db)
{
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
}

void	check_ray(t_db *db)
{
	while (db->hit == 0)
	{
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
		if (db->map->map[db->mapY][db->mapX]
			&& db->map->map[db->mapY][db->mapX] == '1')
			db->hit = 1;
	}
}

void	draw_image(t_db *db, int x)
{
	int	color;
	
	for(int j = 0; j < db->drawStart; j++)
		{
			set_image_pixel(db->w_image, x, j, 3071725);
		}
        for(int y = db->drawStart; y<db->drawEnd; y++)
        {
           int texY = (int)db->texPos & (db->db_img.size - 1);
           db->texPos += db->step;
			if (db->side == 1 && db->rayDirY < 0)
        		color = db->NO[db->db_img.size * texY + db->texX];
			else if (db->side == 1 && db->rayDirY > 0)
        		color = db->SO[db->db_img.size * texY + db->texX];
			else if (db->side == 0 && db->rayDirX < 0)
        		color = db->WE[db->db_img.size * texY + db->texX];
			else if (db->side == 0 && db->rayDirX > 0)
        		color = db->EA[db->db_img.size * texY + db->texX];
			set_image_pixel(db->w_image, x, y, color);
    	}
		for(int j = db->drawEnd; j < S_H; j++)
		{
			set_image_pixel(db->w_image, x, j, 2382603);
		}
}

int game_loop(void *d)
{
    t_db	*db;
	int		color;
	
	color = 0;
    db = d;
    for (int x = 0; x < S_W; x++)
    {
		set_data(db, x);
		calculate_step_sidedist(db);
    	check_ray(db);
        if (db->side == 0)
            db->perpWallDist = (db->sideDistX - db->deltaDistX);
        else
            db->perpWallDist = (db->sideDistY - db->deltaDistY);
    	if (db->side == 0)
        	db->wallX = db->player_y + db->perpWallDist * db->rayDirY;
    	else 
    		db->wallX = db->player_x + db->perpWallDist * db->rayDirX;
    	db->wallX -= floor((db->wallX));
    	db->texX = db->wallX * (double)db->db_img.size;

		if(db->side == 0 && db->rayDirX < 0)
        	db->texX = db->db_img.size - db->texX - 1;
    	if(db->side == 1 && db->rayDirY > 0)
        	db->texX = db->db_img.size - db->texX - 1;
        db->lineHeight = (int)(S_H / db->perpWallDist);
        db->drawStart = -db->lineHeight / 2 + S_H / 2;
        if (db->drawStart < 0)
            db->drawStart = 0;
        db->drawEnd = db->lineHeight / 2 + S_H / 2;
        if (db->drawEnd >= S_H)
            db->drawEnd = S_H - 1;
        db->step = 1.0 * db->db_img.size / db->lineHeight;
        db->texPos = (db->drawStart - S_H / 2 + db->lineHeight / 2) * db->step;
		draw_image(db, x);
    }
	mlx_put_image_to_window(db->mlx, db->win, db->w_image->img, 0, 0);
    return (0);
}
