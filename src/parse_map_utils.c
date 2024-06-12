/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:17:20 by rheck             #+#    #+#             */
/*   Updated: 2024/06/12 11:51:16 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_read_line( char **file)
{
	static int	i;
	char		*line;

	line = ft_strdup(file[i]);
	i++;
	return (line);
}

char	**get_map(char **file)
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
	char	tab[6][6];
	int		tab2[6];
	int		i;
	int		j;

	i = 0;
	j = 0;
	initialise_tabs(tab, tab2);
	while (db->map->texture_path[i] && j < 6)
	{
		if (ft_strncmp(db->map->texture_path[i],
				tab[j], ft_strlen(tab[j])) == 0)
		{
			tab2[j] += 1;
			i++;
			j = -1;
		}
		j++;
	}
	return (verify_texture(j, tab2, i, db));
}

int	is_rounded(t_db *db, int x, int y)
{
	static int	is_close;
	int			map_len;

	if (!db->map->map[0] || !db->map->map[x])
		return (1);
	map_len = ft_strlen(db->map->map[x]);
	if (y == map_len)
	{
		x++;
		y = 0;
	}
	map_len = ft_strlen(db->map->map[x]);
	if (db->map->map[x] && (db->map->map[x][y] == ' '
		|| db->map->map[x][y] == '1'))
		is_rounded(db, x, y + 1);
	if (db->map->map[x] && db->map->map[x][y] == '0')
	{
		if (!db->map->map[x + 1][y] || !db->map->map[x - 1][y] || x == 0
		|| y == 0 || x == map_len - 1 || y == map_len - 1
		|| db->map->map[x - 1][y] == ' ' || db->map->map[x + 1][y] == ' '
		|| db->map->map[x][y - 1] == ' ' || db->map->map[x][y + 1] == ' ' )
		{
			is_close = 1;
			return (is_close);
		}
		is_rounded(db, x, y + 1);
	}
	return (is_close);
}
