/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:58:22 by rheck             #+#    #+#             */
/*   Updated: 2024/06/12 13:33:57 by rheck            ###   ########.fr       */
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

long long	rgb_to_int(double r, double g, double b)
{
	long long	color;

	color = 0;
	printf("r : %f, g : %f b : %f\n", r, g , b);
	color |= (long long)(b * 255);
	color |= (long long)(g * 255) << 8;
	color |= (long long)(r * 255) << 16;
	printf("color : %lld\n", -color);
	return (-color);
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
