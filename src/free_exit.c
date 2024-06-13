/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:04:10 by rheck             #+#    #+#             */
/*   Updated: 2024/06/13 17:36:35 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map(t_map *map)
{
	if(map->map)
		free_array(map->map);
	if(map->texture_path)
		free_array(map->texture_path);
	if(map->rgb_c)
		free(map->rgb_c);
	if(map->rgb_f)
		free(map->rgb_f);	
	free(map);
}

void	free_img(t_img *img)
{
	free(img->img);
	free(img->addr);
}

void	free_array_pos(char **arr, int x)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (i < x)
		{
			free(arr[i]);
			i++;
		}
		free(arr);	
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);	
	}
}

void	exit_end(t_db *db, char *message)
{
	printf("%s\n", message);
	if (db)
	{
		if(db->map)
			free_map(db->map);
		if (db->w_image)
		{
			free(db->w_image);
		}
		free(db);
	}
	system("leaks cub3d");
	exit(EXIT_SUCCESS);
}

void	exit_free(t_db *db, char *message)
{
	printf("%s\n", message);
	if (db)
	{
		if(db->map)
		free_map(db->map);
		if (db->w_image)
			free_img(db->w_image);
		free(db->mlx);
		free(db->win);
		free(db);
	}
	system("leaks cub3d");
	exit(1);
}