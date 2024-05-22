/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:14:11 by rheck             #+#    #+#             */
/*   Updated: 2023/04/11 13:17:49 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_first_index(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && is_set(set, s1[i]))
		i++;
	if (i == (int)ft_strlen(s1))
		return (0);
	return (i);
}

static int	get_last_index(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1);
	while (i >= 0 && is_set(set, s1[i - 1]))
		i--;
	if (i == 0)
		return (0);
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	if (!s1 || !set)
		return (0);
	i = get_first_index(s1, set);
	j = get_last_index(s1, set);
	new = malloc((j - i + 1) * sizeof(char));
	if (!new)
		return (0);
	k = 0;
	while (i < j)
		new[k++] = s1[i++];
	new[k] = 0;
	return (new);
}
