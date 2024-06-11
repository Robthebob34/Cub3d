/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:06:20 by rheck             #+#    #+#             */
/*   Updated: 2024/06/11 16:09:57 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_right(t_db *db)
{
	double oldDirX = db->dir_x;
    db->dir_x = db->dir_x * cos(ROT_SPEED) - db->dir_y * sin(ROT_SPEED);
    db->dir_y = oldDirX * sin(ROT_SPEED) + db->dir_y * cos(ROT_SPEED);
    double oldPlaneX = db->planeX;
    db->planeX = db->planeX * cos(ROT_SPEED) - db->planeY * sin(ROT_SPEED);
    db->planeY = oldPlaneX * sin(ROT_SPEED) + db->planeY * cos(ROT_SPEED);
}

void	move_left(t_db *db)
{
	double oldDirX = db->dir_x;
    db->dir_x = db->dir_x * cos(-ROT_SPEED) - db->dir_y * sin(-ROT_SPEED);
    db->dir_y = oldDirX * sin(-ROT_SPEED) + db->dir_y * cos(-ROT_SPEED);
    double oldPlaneX = db->planeX;
    db->planeX = db->planeX * cos(-ROT_SPEED) - db->planeY * sin(-ROT_SPEED);
    db->planeY = oldPlaneX * sin(-ROT_SPEED) + db->planeY * cos(-ROT_SPEED);
}

void	move_forward(t_db *db)
{
	if(db->map->map[(int)(db->player_y)][(int)(db->player_x + db->dir_x * MOV_SPEED)] != '1')
        db->player_x += db->dir_x * MOV_SPEED;
    if(db->map->map[(int)(db->player_y + db->dir_y * MOV_SPEED)][(int)(db->player_x)] != '1')
        db->player_y += db->dir_y * MOV_SPEED;
}

void	move_backward(t_db *db)
{
	if(db->map->map[(int)(db->player_y)][(int)(db->player_x - db->dir_x * MOV_SPEED)] != '1')
    	db->player_x -= db->dir_x * MOV_SPEED;
    if(db->map->map[(int)(db->player_y - db->dir_y * MOV_SPEED)][(int)(db->player_x)] != '1')
        db->player_y -= db->dir_y * MOV_SPEED;
}

int	key_hook(int keycode, t_db *db)
{
    if (keycode == ESC)
	{
		//free_data(data);
		exit(EXIT_SUCCESS);
	}
	if (keycode == D)
    	move_right(db);
	else if (keycode == A)
    	move_left(db);
	else if (keycode == W)
    	move_forward(db);
	else if (keycode == S)
		move_backward(db);
	return (0);
}
