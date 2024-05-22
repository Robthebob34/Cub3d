/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:12:03 by robinheck         #+#    #+#             */
/*   Updated: 2023/09/28 13:20:27 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_write_string(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

int	ft_write_u_int(unsigned int i)
{
	int		len;
	char	*number;

	len = 0;
	number = ft_itoa_u(i);
	len = ft_write_string(number);
	free(number);
	return (len);
}

int	ft_write_integer(int i)
{
	int		len;
	char	*number;

	len = 0;
	number = ft_itoa(i);
	len = ft_write_string(number);
	free(number);
	return (len);
}
