/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:24:40 by rheck             #+#    #+#             */
/*   Updated: 2023/04/17 00:19:43 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_create_buff(int n)
{
	int	temp;
	int	len;

	len = 1;
	temp = n;
	if (n < 0)
	{
		temp = -n;
		len++;
	}
	while (temp >= 10)
	{
		temp /= 10;
		len++;
	}
	return (len);
}

static char	*ft_int_min(void)
{
	char	*str;

	str = (char *)malloc (12 * sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, "-2147483648", 12);
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		len;

	if (n == -2147483648)
		return (ft_int_min());
	len = ft_create_buff(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	else
		str[0] = '0';
	i = len - 1;
	while (n > 0)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
