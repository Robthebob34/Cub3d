/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:24:22 by rheck             #+#    #+#             */
/*   Updated: 2023/12/04 15:26:11 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*old_s1;
	char	*old_s2;
	int		i;

	i = 0;
	old_s1 = s1;
	old_s2 = s2;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1)+ ft_strlen(s2) + 1));
	if (str == 0)
		return (0);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	free(old_s1);
	free(old_s2);
	return (str);
}
