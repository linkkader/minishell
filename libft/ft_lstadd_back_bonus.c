/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:20:49 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/23 19:07:11 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (alst != NULL)
	{
		temp = alst[0];
		if (temp == NULL)
		{
			alst[0] = new;
			return ;
		}
		while (alst[0] != NULL)
		{
			if (alst[0]->next == NULL)
				break ;
			alst[0] = alst[0]->next;
		}
		alst[0]->next = new;
		alst[0] = temp;
	}
}
