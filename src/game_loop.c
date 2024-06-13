/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:04:29 by rheck             #+#    #+#             */
/*   Updated: 2024/06/13 14:07:57 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_data(t_db *db, int x)
{
	db->camera_x = 2 * x / (double)S_W - 1;
	db->ray_dir_x = db->dir_x + db->plane_x * db->camera_x;
	db->ray_dir_y = db->dir_y + db->plane_y * db->camera_x;
	db->delta_dist_x = fabs(1 / db->ray_dir_x);
	db->delta_dist_y = fabs(1 / db->ray_dir_y);
	db->map_x = (int)db->player_x;
	db->map_y = (int)db->player_y;
	db->delta_dist_x = sqrt(1 + (db->ray_dir_y * db->ray_dir_y)
			/ (db->ray_dir_x * db->ray_dir_x));
	db->delta_dist_y = sqrt(1 + (db->ray_dir_x * db->ray_dir_x)
			/ (db->ray_dir_y * db->ray_dir_y));
	db->hit = 0;
}

void	calculate_step_sidedist(t_db *db)
{
	if (db->ray_dir_x < 0)
	{
		db->step_x = -1;
		db->side_dist_x = (db->player_x - db->map_x) * db->delta_dist_x;
	}
	else
	{
		db->step_x = 1;
		db->side_dist_x = (db->map_x + 1.0 - db->player_x) * db->delta_dist_x;
	}
	if (db->ray_dir_y < 0)
	{
		db->step_y = -1;
		db->side_dist_y = (db->player_y - db->map_y) * db->delta_dist_y;
	}
	else
	{
		db->step_y = 1;
		db->side_dist_y = (db->map_y + 1.0 - db->player_y) * db->delta_dist_y;
	}
}

void	check_ray(t_db *db)
{
	while (db->hit == 0)
	{
		if (db->side_dist_x < db->side_dist_y)
		{
			db->side_dist_x += db->delta_dist_x;
			db->map_x += db->step_x;
			db->side = 0;
		}
		else
		{
			db->side_dist_y += db->delta_dist_y;
			db->map_y += db->step_y;
			db->side = 1;
		}
		if (db->map->map[db->map_y][db->map_x]
			&& db->map->map[db->map_y][db->map_x] == '1')
			db->hit = 1;
	}
}

void	calculation(t_db *db)
{
	if (db->side == 0)
		db->p_wall_dist = (db->side_dist_x - db->delta_dist_x);
	else
		db->p_wall_dist = (db->side_dist_y - db->delta_dist_y);
	if (db->side == 0)
		db->wall_x = db->player_y + db->p_wall_dist * db->ray_dir_y;
	else
		db->wall_x = db->player_x + db->p_wall_dist * db->ray_dir_x;
	if (db->p_wall_dist <= 0.15)
		db->p_wall_dist = 0.15;
	db->wall_x -= floor((db->wall_x));
	db->tex_x = db->wall_x * (double)db->db_img.size;
	if (db->side == 0 && db->ray_dir_x < 0)
		db->tex_x = db->db_img.size - db->tex_x - 1;
	if (db->side == 1 && db->ray_dir_y > 0)
		db->tex_x = db->db_img.size - db->tex_x - 1;
	db->line_height = (int)(S_H / db->p_wall_dist);
	db->draw_start = -db->line_height / 2 + S_H / 2;
	if (db->draw_start < 0)
		db->draw_start = 0;
	db->draw_end = db->line_height / 2 + S_H / 2;
	if (db->draw_end >= S_H)
		db->draw_end = S_H - 1;
	db->step = 1.0 * db->db_img.size / db->line_height;
	db->tex_pos = (db->draw_start - S_H / 2 + db->line_height / 2) * db->step;
}

int	game_loop(void *d)
{
	t_db	*db;
	int		color;
	int		x;

	x = 0;
	color = 0;
	db = d;
	while (x < S_W)
	{
		set_data(db, x);
		calculate_step_sidedist(db);
		check_ray(db);
		calculation(db);
		draw_image(db, x);
		x++;
	}
	mlx_put_image_to_window(db->mlx, db->win, db->w_image->img, 0, 0);
	draw_minimap(db);
	return (0);
}
