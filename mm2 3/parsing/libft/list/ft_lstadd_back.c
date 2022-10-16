/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:46:44 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/18 18:46:47 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	p_ft_lstadd_back(t_command **lst, t_command *new)
{
	t_command	*last;

	if (lst)
	{
		if (*lst)
		{
			last = p_ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
