/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:35:07 by rheck             #+#    #+#             */
/*   Updated: 2024/06/11 15:20:51 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_player_position(t_db *db)
{
	int	i;
	int	j;

	i = 0;
	while(db->map->map[i])
	{
		j = 0;
		while(db->map->map[i][j])
		{
			if (db->map->map[i][j] == 'N' || db->map->map[i][j] == 'E'
				|| db->map->map[i][j] == 'W' || db->map->map[i][j] == 'S')
			{
				db->player_y = i + 0.5;
				db->player_x = j + 0.5;
				db->orientation = db->map->map[i][j];
			}
			j++;
		}
		i++;
	}
}
