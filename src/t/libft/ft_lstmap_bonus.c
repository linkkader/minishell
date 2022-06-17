/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:25:02 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/13 18:28:39 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	(void)del;
	new = NULL;
	if (lst != NULL)
	{
		if (f != NULL)
			new = ft_lstnew(f(lst->content));
		if (new == NULL)
			return (NULL);
		lst = lst->next;
	}
	while (lst != NULL)
	{
		if (f != NULL)
			temp = ft_lstnew(f(lst->content));
		if (temp == NULL)
			return (NULL);
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
