/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:46 by rheck             #+#    #+#             */
/*   Updated: 2024/05/22 11:21:48 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

char	*empty_line(char **tmp, char **start_str)
{
	int	i;

	i = 0;
	if (*start_str)
	{
		while ((*start_str)[i])
		{
			(*start_str)[i] = 0;
			i++;
		}
		free(*start_str);
		*start_str = NULL;
	}
	free(*tmp);
	*tmp = NULL;
	return (NULL);
}

char	*ft_readed_line(char *start)
{
	int		i;
	char	*line;

	if (!start || !start[0])
		return (NULL);
	i = 0;
	while (start[i] && start[i] != '\n')
		i++;
	if (start[i] == '\n')
		i++;
	line = (char *)malloc(1 + i * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (start[i] && start[i] != '\n')
	{
		line[i] = start[i];
		i++;
	}
	if (start[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_move_start(char	*start)
{
	char	*new_buff;
	int		i;
	int		j;

	i = 0;
	if (!start)
		return (NULL);
	while (start[i] && start[i] != '\n')
		i++;
	if (start[i] == '\0')
		return (free(start), NULL);
	i += (start[i] == '\n');
	new_buff = (char *)malloc(1 + ft_strlen_gnl(start) - i);
	if (!new_buff)
		return (free(start), NULL);
	j = 0;
	while (start[i + j])
	{
		new_buff[j] = start[i + j];
		j++;
	}
	new_buff[j] = '\0';
	free(start);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	int			fd_read;
	static char	*start_str = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	fd_read = 1;
	tmp = (char *)malloc(1 + BUFFER_SIZE * sizeof(char));
	if (!tmp)
		return (NULL);
	while (!(ft_strchr_gnl(start_str, '\n')) && fd_read != 0)
	{
		fd_read = read(fd, tmp, BUFFER_SIZE);
		if (fd_read == -1)
			return (empty_line(&tmp, &start_str));
		tmp[fd_read] = '\0';
		start_str = ft_strjoin_gnl(start_str, tmp);
	}
	free(tmp);
	tmp = ft_readed_line(start_str);
	start_str = ft_move_start(start_str);
	return (tmp);
}
