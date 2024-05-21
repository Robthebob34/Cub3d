/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robinheck <robinheck@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:01:33 by robinheck         #+#    #+#             */
/*   Updated: 2024/05/21 12:00:01 by robinheck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int verify_extensention(char *file)
{
    int len;

    len = ft_strlen(file);
    if (len >= 5 && file[len - 2] == 'u' && file[len - 3] == 'c' && file[len - 4] == '.')
        return (1);
	printf("Error\nWrong map extension\n");
    return (0);
}

// int is_map_closed (char **map)
// {
	
// }

char	*create_long_map(char *file)
{
	char	*long_map;
	char	*tmp;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nInvalid map_path\n");
		exit(EXIT_FAILURE);
	}
	long_map = get_next_line(fd);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
		{
			free(tmp);
			break ;
		}
		long_map = ft_strjoin(long_map, tmp);
	}
	close (fd);
	return (long_map);
}
char	**map_tab(char *long_map)
{
	char **map;
	
	if (!long_map)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	map = ft_split(long_map, '\n');
	free(long_map);
	return (map);
}

int parse_map(char *file)
{
	
    return (verify_extensention(file));
}