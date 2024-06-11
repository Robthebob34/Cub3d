/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:17:20 by rheck             #+#    #+#             */
/*   Updated: 2024/06/11 15:20:34 by rheck            ###   ########.fr       */
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
	printf("length %d\n", length);
	if (length <= 5)
		return (NULL);
	map = malloc((length - 5) * sizeof(char *));
	if (!map)
		return (NULL);
	while (i < length)
	{
		map[index] = ft_read_line(file);
		index++;
		i++;
	}
	map[index] = NULL;
	return (map);
}

void	load_texture(t_db *db, char *t_path)
{
	int	length;

	length = ft_strlen(t_path);
	length -= 5;
	while (length >= 0 && t_path[length] != '.')
		length--;
	if (length > 0)
	{
		if (t_path[0] == 'N' && t_path[1] == 'O')
			db->path_north = ft_strdup(t_path + length);
		else if (t_path[0] == 'S' && t_path[1] == 'O')
			db->path_south = ft_strdup(t_path + length);
		else if (t_path[0] == 'W' && t_path[1] == 'E')
			db->path_west = ft_strdup(t_path + length);
		else if (t_path[0] == 'E' && t_path[1] == 'A')
			db->path_east = ft_strdup(t_path + length);
		return ;
	}
	length = ft_strlen(t_path);
	while (length >= 0 && t_path[length] != ' ')
		length--;
	if (t_path[0] == 'F')
		db->floor_color = ft_strdup(t_path + length + 1);
	else if (t_path[0] == 'C')
		db->cieling_color = ft_strdup(t_path + length + 1);
}

int	check_texture(t_db *db)
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
	i = 0;
	while(db->map->texture_path[i])
	{
		load_texture(db, db->map->texture_path[i]);
		i++;
	}
	return (1);
}

int is_rounded(t_db *db, int x, int y)
{
    static int is_close;
	int	map_len;

	if (!db->map->map[0] || !db->map->map[x])
		return (1);
	map_len = ft_strlen(db->map->map[x]);
    if(y == map_len)
    {
        x++;
        y = 0;
    }
	map_len = ft_strlen(db->map->map[x]);
    if( db->map->map[x] && (db->map->map[x][y] == ' '
		|| db->map->map[x][y] == '1'))
        is_rounded(db, x, y + 1);
    if(db->map->map[x] && db->map->map[x][y] == '0')
    {
        if(!db->map->map[x + 1][y] || !db->map->map[x - 1][y] || x == 0 || y == 0 || x == map_len - 1 || y == map_len - 1
		|| db->map->map[x - 1][y] == ' ' || db->map->map[x + 1][y] == ' ' 
        || db->map->map[x][y - 1] == ' ' || db->map->map[x][y + 1] == ' ' )
		{
			is_close = 1;
			return (is_close);
		}
        is_rounded(db, x, y + 1);
    }
    return(is_close);
}
