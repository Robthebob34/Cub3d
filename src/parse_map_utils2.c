/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:02:58 by rheck             #+#    #+#             */
/*   Updated: 2024/05/27 17:38:05 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	chars_check(char c)
{
	if (c != '1' && c != '0' && c != ' ' && c != 'N' && c != 'E' && c != 'W'
		&& c != 'S')
		return (1);
	return (0);
}

int	verfiy_characters(t_db *db)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = 0;
	if (!db->map->map)
		return (0);
	while(db->map->map[i])
	{
		j = 0;
		while(db->map->map[i][j])
		{
			if (chars_check(db->map->map[i][j]))
				return (0);
			if (db->map->map[i][j] == 'N' || db->map->map[i][j] == 'E'
				|| db->map->map[i][j] == 'W' || db->map->map[i][j] == 'S')
				player++;
			j++;
		}
		i++;
	}
	if (player == 1)
		return (1);
	return (0);
}
