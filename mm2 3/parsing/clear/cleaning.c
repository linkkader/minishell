/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:44:51 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/21 22:06:18 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleaning(t_command **cmds, int ***pipes, char close_pipe)
{
	t_command	*tmp;

	tmp = *cmds;
	if (close_pipe)
		close_all(p_ft_lstsize(*cmds), pipes);
	clear_tokens(&tmp);
	p_ft_lstclear(cmds);
}
