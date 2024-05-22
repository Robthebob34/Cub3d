/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:22:33 by rheck             #+#    #+#             */
/*   Updated: 2023/04/11 15:28:56 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	if (!del)
		return ;
	if (lst != NULL && del != NULL)
	{
		current = *lst;
		while (current != NULL)
		{
			*lst = current->next;
			del(current->content);
			free(current);
			current = *lst;
		}
	}
	*lst = NULL;
}
