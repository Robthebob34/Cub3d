/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:58:22 by rheck             #+#    #+#             */
/*   Updated: 2024/06/12 14:17:06 by rheck            ###   ########.fr       */
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
	set_direction(db);
}

int	rgb_to_int(int r, int g, int b)
{
	int	color;

	color = 0;
	color |= b;
	color |= g << 8;
	color |= r << 16;
	return (color);
}

int	destroy_window(t_db *data)
{
	if (data != NULL)
	{
		if (data->mlx != NULL && data->win != NULL)
			mlx_destroy_window(data->mlx, data->win);
	}
	exit(EXIT_SUCCESS);
}
