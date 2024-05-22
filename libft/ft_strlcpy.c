/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:24:19 by rheck             #+#    #+#             */
/*   Updated: 2023/04/11 13:13:22 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	offset;

	offset = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize > 0)
	{
		while (*(src + offset) != '\0' && offset < dstsize - 1)
		{
			if (offset == dstsize)
			{
				offset --;
				break ;
			}
			*(dst + offset) = *(src + offset);
			offset ++;
		}
	}
	*(dst + offset) = '\0';
	while (*(src + offset) != '\0')
		offset ++;
	return (offset);
}
