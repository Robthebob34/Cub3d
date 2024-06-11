/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:14:42 by rheck             #+#    #+#             */
/*   Updated: 2024/06/11 17:47:36 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_wall(t_db *db, int x, int j)
{
	int	color;
	int	tex_y;

	color = 0;
	tex_y = (int)db->texPos & (db->db_img.size - 1);
	db->texPos += db->step;
	if (db->side == 1 && db->rayDirY < 0)
		color = db->NO[db->db_img.size * tex_y + db->texX];
	else if (db->side == 1 && db->rayDirY > 0)
		color = db->SO[db->db_img.size * tex_y + db->texX];
	else if (db->side == 0 && db->rayDirX < 0)
		color = db->WE[db->db_img.size * tex_y + db->texX];
	else if (db->side == 0 && db->rayDirX > 0)
		color = db->EA[db->db_img.size * tex_y + db->texX];
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
