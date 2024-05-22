/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:03:07 by rheck             #+#    #+#             */
/*   Updated: 2023/04/11 13:03:11 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*l1;
	const unsigned char	*l2;

	l1 = s1;
	l2 = s2;
	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (*l1 == *l2 && i < n - 1)
	{
		l1++;
		l2++;
		i++;
	}
	return (*l1 - *l2);
}
