/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:46:53 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/18 18:46:57 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*p_ft_lstlast(t_command *lst)
{
	t_command	*head;

	head = lst;
	if (!lst)
		return (lst);
	while (head->next)
		head = head->next;
	return (head);
}
