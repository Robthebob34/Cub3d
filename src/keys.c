/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:06:20 by rheck             #+#    #+#             */
/*   Updated: 2024/06/11 15:06:43 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
      db->dir_x = db->dir_x * cos(ROT_SPEED) - db->dir_y * sin(ROT_SPEED);
      db->dir_y = oldDirX * sin(ROT_SPEED) + db->dir_y * cos(ROT_SPEED);
      double oldPlaneX = db->planeX;
      db->planeX = db->planeX * cos(ROT_SPEED) - db->planeY * sin(ROT_SPEED);
      db->planeY = oldPlaneX * sin(ROT_SPEED) + db->planeY * cos(ROT_SPEED);
	}
	if (keycode == A)
	{
      double oldDirX = db->dir_x;
      db->dir_x = db->dir_x * cos(-ROT_SPEED) - db->dir_y * sin(-ROT_SPEED);
      db->dir_y = oldDirX * sin(-ROT_SPEED) + db->dir_y * cos(-ROT_SPEED);
      double oldPlaneX = db->planeX;
      db->planeX = db->planeX * cos(-ROT_SPEED) - db->planeY * sin(-ROT_SPEED);
      db->planeY = oldPlaneX * sin(-ROT_SPEED) + db->planeY * cos(-ROT_SPEED);
	}
	if (keycode == W)
	{
        if(db->map->map[(int)(db->player_y)][(int)(db->player_x + db->dir_x * MOV_SPEED)] != '1')
            db->player_x += db->dir_x * MOV_SPEED;
        if(db->map->map[(int)(db->player_y + db->dir_y * MOV_SPEED)][(int)(db->player_x)] != '1')
            db->player_y += db->dir_y * MOV_SPEED;
	}
	if (keycode == S)
	{
		if(db->map->map[(int)(db->player_y)][(int)(db->player_x - db->dir_x * MOV_SPEED)] != '1')
            db->player_x -= db->dir_x * MOV_SPEED;
        if(db->map->map[(int)(db->player_y - db->dir_y * MOV_SPEED)][(int)(db->player_x)] != '1')
            db->player_y -= db->dir_y * MOV_SPEED;
    }
	return (0);
}
