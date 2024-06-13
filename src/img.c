/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:00:25 by rheck             #+#    #+#             */
/*   Updated: 2024/06/13 14:55:19 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	*xpm_to_img(t_db *data, char *path)
{
	int		*buffer;
	int		x;
	int		y;

	if (!path)
		exit_free(data, "Error\nPath corrupted");
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
	return (buffer);
}

void	init_textures(t_db *data)
{
	data->no = xpm_to_img(data, data->path_north);
	data->so = xpm_to_img(data, data->path_south);
	data->ea = xpm_to_img(data, data->path_east);
	data->we = xpm_to_img(data, data->path_west);
	set_colors(data);
}

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

void	init_img(t_db *data)
{
	data->w_image->img = mlx_new_image(data->mlx, S_W, S_H);
	if (data->w_image->img == NULL)
		exit_free(data, "Error\nLoading Image");
	data->w_image->addr = (int *)mlx_get_data_addr(data->w_image->img,
			&data->w_image->pixel_bits,
			&data->w_image->size_line, &data->w_image->endian);
	return ;
}

void	image_init(t_db *db, char *path)
{
	db->db_img.img = mlx_xpm_file_to_image(db->mlx, path,
			&db->db_img.size, &db->db_img.size);
	//free and exit properly
	if (!db->db_img.img)
		exit_free(db, "Error\nLoading Image") ;
	db->db_img.addr = (int *)mlx_get_data_addr(db->db_img.img,
			&db->db_img.pixel_bits,
			&db->db_img.size_line, &db->db_img.endian);
}
