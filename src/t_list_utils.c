/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert3_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:38:23 by acouliba          #+#    #+#             */
/*   Updated: 2022/04/11 17:38:25 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	push(t_list **lst, char *str)
{
	ft_lstadd_back(lst, ft_lstnew(ft_strdup(str)));
}