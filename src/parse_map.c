/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:01:33 by robinheck         #+#    #+#             */
/*   Updated: 2024/06/13 14:43:13 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	verify_extensention(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len >= 5 && file[len - 2] == 'u'
		&& file[len - 3] == 'c' && file[len - 4] == '.')
		return (1);
	printf("Error\nWrong map extension\n");
	return (0);
}

char	**get_data(char **file)
{
	char	**data;
	int		i;

	i = 0;
	data = NULL;
	data = malloc(7 * sizeof(char *));
	if (!data)
		return (data);
	while (i < 6)
	{
		data[i] = ft_read_line(file);
		if (data[i] == NULL)
		{
			free_array_pos(data, i);
			break ;
		}
		i++;
	}
	data[i] = NULL;
	return (data);
}

char	*read_file(char *file)
{
	char	*long_file;
	char	*tmp;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nInvalid map_path\n");
		exit(EXIT_FAILURE);
	}
	long_file = get_next_line(fd);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
		{
			free(tmp);
			break ;
		}
		long_file = ft_strjoin(long_file, tmp);
	}
	close (fd);
	return (long_file);
}

char	**remake_file(char *long_file)
{
	char	**file;

	if (!long_file)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	file = ft_split(long_file, '\n');
	free(long_file);
	return (file);
}

int	parse_map(char *file_path, t_db *db)
{
	char	**file;

	file = remake_file(read_file(file_path));
	if (!file)
		return (0);
	db->map->texture_path = get_data(file);
	if (!db->map->texture_path)
		exit(1);
	db->map->map = get_map(file);
	if (!db->map->map)
	{
		free_array(file);
		exit(1);
	}
	return (verify_extensention(file_path) && check_texture(db)
		&& !is_rounded(db, 0, 0) && verfiy_characters(db));
}
