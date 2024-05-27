/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:02:58 by rheck             #+#    #+#             */
/*   Updated: 2024/05/23 14:08:23 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	verfiy_characters(t_db *db)
{
	int	i;
	int	j;

	i = 0;
	if (!db->map->map)
		return (0);
	while(db->map->map[i])
	{
		j = 0;
		while(db->map->map[i][j])
		{
			if (db->map->map[i][j] != '1' &&db->map->map[i][j] != '0'
				&& db->map->map[i][j] != 'N' && db->map->map[i][j] != 'E'
				&& db->map->map[i][j] != 'W' && db->map->map[i][j] != 'S'
				&& db->map->map[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}