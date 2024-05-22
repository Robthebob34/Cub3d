/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:45:55 by robinheck         #+#    #+#             */
/*   Updated: 2023/09/28 12:47:28 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_type(va_list args, char c)
{
	int	nb;

	nb = 0;
	if (c == 'c')
		nb += ft_putchar(va_arg(args, int));
	else if (c == 's')
		nb += ft_write_string(va_arg(args, char *));
	else if (c == 'p')
		nb += ft_write_pointer(va_arg(args, void *));
	else if (c == 'd')
		nb += ft_write_integer(va_arg(args, int));
	else if (c == 'i')
		nb += ft_write_integer(va_arg(args, int));
	else if (c == 'u')
		nb += ft_write_u_int(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		nb += ft_write_hexa((va_arg(args, unsigned int)), c);
	else if (c == '%')
		nb += ft_write_percent();
	return (nb);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		nb_printed;
	va_list	args;

	if (!str)
		return (0);
	i = 0;
	nb_printed = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			nb_printed += get_type(args, str[i + 1]);
			i += 2;
		}
		else
		{
			nb_printed += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(args);
	return (nb_printed);
}
