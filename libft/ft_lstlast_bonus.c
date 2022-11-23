/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:19:58 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/20 15:09:01 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*head;

	head = lst;
	if (!lst)
		return (lst);
	while (head->next)
		head = head->next;
	return (head);
}
/*#include <stdio.h>
int	main()
{
	t_list	*l;
	ft_lstadd_front(&l, ft_lstnew("tah"));
	l = ft_lstlast(l);
	printf("%s\n", l->content);
}*/
