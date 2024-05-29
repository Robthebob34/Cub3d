/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:58:22 by rheck             #+#    #+#             */
/*   Updated: 2024/05/29 15:13:13 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int rgb_to_int(double r, double g, double b)
{
    int color;

	color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
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