/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/22 11:25:35 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	run(t_cmd *temp, pid_t *pids, int *i)
{
	pids[*i] = fork();
	if (pids[*i] == 0)
	{
		check_builtin(temp);
		if (temp->path != NULL)
		{
			dup2(temp->in, 0);
			dup2(temp->out, 1);
			if (temp->in != 0)
				close(temp->in);
			if (temp->out != 1)
				close(temp->out);
			(execve(temp->path, temp->args, g_global.env));
		}
		else
			exit(0);
	}
	if (temp->in != 0)
		close(temp->in);
	if (temp->out != 1)
		close(temp->out);
}

void	run_all(t_cmd *cmd, pid_t *pids)
{
	int			i;
	sig_t		sig[2];
	t_cmd		*temp;

	temp = cmd;
	i = 0;
	sig[0] = signal(SIGINT, sigint_handler_in_process);
	sig[1] = signal(SIGQUIT, sigquit_handler_in_process);
	while (temp)
	{
		run(temp, pids, &i);
		i++;
		temp = temp->next;
	}
	wait(&g_global.exit_code);
	while (i > 0)
	{
		i--;
		waitpid(pids[i], NULL, 0);
	}
	g_global.exit_code = WEXITSTATUS(g_global.exit_code);
	signal(SIGINT, sig[0]);
	signal(SIGQUIT, sig[1]);
}
