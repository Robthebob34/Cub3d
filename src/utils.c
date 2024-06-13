/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:14:42 by rheck             #+#    #+#             */
/*   Updated: 2024/06/13 14:45:58 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_direction_2(t_db *db)
{
	if (db->orientation == 'S')
	{
		db->plane_x = -0.66;
		db->plane_y = 0;
		db->dir_x = 0;
		db->dir_y = 1;
	}
	else if (db->orientation == 'W')
	{
		db->plane_x = 0;
		db->plane_y = -0.66;
		db->dir_x = -1;
		db->dir_y = 0;
	}
}

void	set_direction(t_db *db)
{
	if (db->orientation == 'N')
	{
		db->plane_x = 0.66;
		db->plane_y = 0;
		db->dir_x = 0;
		db->dir_y = -1;
	}
	else if (db->orientation == 'E')
	{
		db->plane_x = 0;
		db->plane_y = 0.66;
		db->dir_x = 1;
		db->dir_y = 0;
	}
	set_direction_2(db);
}

void	draw_wall(t_db *db, int x, int j)
{
	int	color;
	int	tex_y;

	color = 0;
	tex_y = (int)db->tex_pos & (db->db_img.size - 1);
	db->tex_pos += db->step;
	if (db->side == 1 && db->ray_dir_y < 0)
		color = db->no[db->db_img.size * tex_y + db->tex_x];
	else if (db->side == 1 && db->ray_dir_y > 0)
		color = db->so[db->db_img.size * tex_y + db->tex_x];
	else if (db->side == 0 && db->ray_dir_x < 0)
		color = db->we[db->db_img.size * tex_y + db->tex_x];
	else if (db->side == 0 && db->ray_dir_x > 0)
		color = db->ea[db->db_img.size * tex_y + db->tex_x];
	set_image_pixel(db->w_image, x, j, color);
}

int	verify_texture(int j, int tab2[], int i, t_db *db)
{
	if (j == 6 || tab2[0] != 1 || tab2[1] != 1 || tab2[2] != 1
		|| tab2[3] != 1 || tab2[4] != 1 || tab2[5] != 1)
		return (0);
	i = 0;
	while (db->map->texture_path[i])
	{
		load_texture(db, db->map->texture_path[i]);
		i++;
	}
	return (1);
}

void	initialise_tabs(char tab[6][6], int tab2[6])
{
	ft_strlcpy(tab[0], "NO", 6);
	ft_strlcpy(tab[1], "SO", 6);
	ft_strlcpy(tab[2], "WE", 6);
	ft_strlcpy(tab[3], "EA", 6);
	ft_strlcpy(tab[4], "F", 6);
	ft_strlcpy(tab[5], "C", 6);
	tab2[0] = 0;
	tab2[1] = 0;
	tab2[2] = 0;
	tab2[3] = 0;
	tab2[4] = 0;
	tab2[5] = 0;
}
