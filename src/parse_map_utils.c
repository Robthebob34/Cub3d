/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:17:20 by rheck             #+#    #+#             */
/*   Updated: 2024/05/22 14:07:19 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char *ft_read_line( char **file)
{
	static int	i;
	char		*line;
	
	line = ft_strdup(file[i]);
	i++;
	return (line);
}

char **get_map(char **file)
{
	char	**map;
	int		i;
	int		length;
	int		index;
	
	i = 6;
	index = 0;
	length = 0;
	map = NULL;
	while (file[length])
		length++;
	map = malloc((length - 5) * sizeof(char *));
	if (!map)
		return (map);
	while (i < length)
	{
		map[index] = ft_read_line(file);
		index++;
		i++;
	}
	map[index] = NULL;
	return (map);
}

int	load_texture(t_db *db)
{
	char tab[][6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int	tab2[6] = {0, 0, 0, 0, 0, 0};
	int i = 0;
	int j = 0;
	while(db->map->texture_path[i] && j < 6)
	{
		if(ft_strncmp(db->map->texture_path[i], tab[j], ft_strlen(tab[j])) == 0)
		{
			tab2[j] += 1;
			i++;
			j = -1;
		}
		j++;
	}
	if(j == 6 || tab2[0] != 1 || tab2[1] != 1 || tab2[2] != 1
		|| tab2[3] != 1 || tab2[4] != 1 || tab2[5] != 1)
		return (0);
	else
		return (1);
}
