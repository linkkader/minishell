/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:02:50 by acouliba          #+#    #+#             */
/*   Updated: 2022/11/29 17:02:59 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	my_pipe(t_cmd *cmd)
{
	int		fd[2];
	int		next_in;

	next_in = dup(STDIN_FILENO);
	while (cmd)
	{
		if (cmd->next == NULL)
		{
			cmd->out = dup(STDOUT_FILENO);
			cmd->in = next_in;
		}
		else
		{
			cmd->in = next_in;
			pipe(fd);
			cmd->out = fd[1];
			next_in = fd[0];
		}
		cmd = cmd->next;
	}
}
