/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:02:47 by robinheck         #+#    #+#             */
/*   Updated: 2023/09/28 13:20:07 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_convert_ptr(unsigned long num)
{
	if (num >= 16)
	{
		ft_convert_ptr(num / 16);
		ft_convert_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	ft_ptr_len(unsigned long num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

int	ft_write_pointer(void *p)
{
	int				nb_char;
	unsigned long	s;

	s = (unsigned long) p;
	nb_char = 0;
	nb_char += write(1, "0x", 2);
	if (s == 0)
		nb_char += write(1, "0", 1);
	else
	{
		ft_convert_ptr(s);
		nb_char += ft_ptr_len(s);
	}
	return (nb_char);
}
