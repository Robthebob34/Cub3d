/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:08:55 by rheck             #+#    #+#             */
/*   Updated: 2023/12/04 15:51:25 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *src, int n)
{
	int		src_len;
	char	*pnt;
	int		i;

	src_len = ft_strlen(src);
	pnt = malloc((n + 1) * sizeof(char));
	if (!pnt)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		pnt[i] = src[i];
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
}

static int	splited_arr_len(char *s, char c)
{
	int		i;
	int		strs_splited_ln;

	i = 0;
	strs_splited_ln = 0;
	if (!(s[0] == c) && s[0] != '\0')
		strs_splited_ln++;
	while (s[i])
	{
		if (s[i] == c && !(s[i + 1] == c)
			&& s[i + 1] != '\0')
			strs_splited_ln++;
		i++;
	}
	return (strs_splited_ln);
}

static char	**ft_abort(char **s, int k)
{
	while (k >= 0)
		free(s[k--]);
	free(s);
	return (NULL);
}

static char	**ft_process(const char *s, char c, int ln, char **strs_splited)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (!(s[i] == c) && s[i] != '\0')
			i++;
		if (i > j)
			strs_splited[k++] = ft_strndup(&s[j], i - j);
		if (i > j && strs_splited[k - 1] == NULL)
			return (ft_abort(strs_splited, k - 1));
	}
	strs_splited[ln] = NULL;
	return (strs_splited);
}

char	**ft_split(const char *s, char c)
{
	int		strs_splited_ln;
	char	**strs_splited;

	if (!s)
		return (0);
	strs_splited_ln = splited_arr_len((char *)s, c);
	strs_splited = malloc((strs_splited_ln + 1) * sizeof(char *));
	if (!strs_splited)
		return (NULL);
	return (ft_process(s, c, strs_splited_ln, strs_splited));
}
