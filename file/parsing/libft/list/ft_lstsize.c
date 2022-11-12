/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:47:02 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/18 18:47:04 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	p_ft_lstsize(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}
