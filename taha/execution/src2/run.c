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
	check_builtin(temp);
	pids[*i] = fork();
	if (pids[*i] == 0)
	{
		if (temp->path != NULL)
		{
			dup2(temp->in, STDIN_FILENO);
			dup2(temp->out, STDOUT_FILENO);
			close_all(g_global.cmds);
			(execve(temp->path, temp->args, g_global.env));
		}
		exit(0);
	}
	close(temp->in);
	if (temp->out != 1)
		close(temp->out);
}

void	run_all(t_cmd *cmd, pid_t *pids)
{
	int			i;
	sig_t		sig[2];
	t_cmd		*temp;
	int 		i2;

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
	i2 = 0;
	while (i2 > i)
	{
		waitpid(pids[i2], &g_global.exit_code, 0);
		i++;
	}
	//normal_echo();
	g_global.exit_code = WEXITSTATUS(g_global.exit_code);
	signal(SIGINT, sig[0]);
	signal(SIGQUIT, sig[1]);
	//correct_echo();
}
