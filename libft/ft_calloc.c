/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:30:05 by rheck             #+#    #+#             */
/*   Updated: 2023/04/11 12:51:29 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*data;
	size_t	check;

	check = count * size;
	if (count && check / count != size)
		return (NULL);
	data = malloc(count * size);
	if (data == 0)
		return (data);
	ft_bzero(data, count * size);
	return (data);
}
