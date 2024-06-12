/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:09:46 by rheck             #+#    #+#             */
/*   Updated: 2024/06/12 13:34:51 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_colors(t_db *db)
{
	char	**colors;

	colors = ft_split(db->cieling_color, ',');
	db->c_r = ft_atoi(colors[0]);
	db->c_g = ft_atoi(colors[1]);
	db->c_b = ft_atoi(colors[2]);
	db->c_color = rgb_to_int(db->c_r, db->c_g,db->c_b);
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
	colors = ft_split(db->floor_color, ',');
	db->f_r = ft_atoi(colors[0]);
	db->f_g = ft_atoi(colors[1]);
	db->f_b = ft_atoi(colors[2]);
	db->f_color = rgb_to_int(db->f_r, db->f_g,db->f_b);
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
}
