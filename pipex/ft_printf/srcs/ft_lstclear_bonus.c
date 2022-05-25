/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:23:12 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/23 19:03:45 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp2;

	if (lst != NULL)
	{
		temp = lst[0];
		while (temp != NULL)
		{
			temp2 = temp;
			temp = temp->next;
			ft_lstdelone(temp2, del);
		}
		lst[0] = NULL;
	}
}
