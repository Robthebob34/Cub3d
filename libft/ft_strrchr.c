/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:49:00 by rheck             #+#    #+#             */
/*   Updated: 2023/04/11 13:16:34 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = 0;
	while (*s != 0)
	{
		if (*s == (char)c)
			last = ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (last);
}
