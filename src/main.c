/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:55:28 by robinheck         #+#    #+#             */
/*   Updated: 2024/05/28 17:56:33 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mlx_start(t_db *db)
{
	if (!db->mlx)
	{
		exit(EXIT_FAILURE);
	}
	db->win = mlx_new_window(db->mlx, 2048, 
	 		 1024, "cub3d");
	if (!db->win)
	{
		exit(EXIT_FAILURE);
	}
	
}

void game_loop(void *d) // game loop
{
	t_db *db;

	db = d;
	mlx_destroy_image(db->mlx, db->img); // delete the image
	db->img = mlx_new_image(db->mlx, 2048, 1024); // create new image
	mlx_put_image_to_window(db->mlx,db->win, db->img, 0, 0); // put the image to the window
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
	db->mlx = mlx_init();
	mlx_start(db);
	mlx_hook(db->win, 17, 0, destroy_window, NULL);
	mlx_loop_hook(db->mlx, &game_loop, &db); // game loop continuously call a specified function to update the game state and render the frames.
	//mlx_key_hook(db->mlx, &mlx_key, &db); // key press and release
	mlx_loop(db->mlx); // mlx loop
	return (0);
}


