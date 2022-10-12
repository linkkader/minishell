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

static int	exe(t_cmd *temp)
{
	dup2(temp->in, 0);
	dup2(temp->out, 1);
	if (temp->in != 0)
		close(temp->in);
	if (temp->out != 1)
		close(temp->in);
	return (execve(temp->args[0], temp->args + 1, g_global.env));
	exit (2);
}

void	run(t_cmd *temp, pid_t *pids)
{
	char	**args;
	int		i;

	i = 0;
	args = check_cmd(temp);
	if (args == NULL)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			temp->error = exe(temp);
	}
	else if (args != NULL)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			temp->error = exe(temp);;
	}
	if (temp->in != 0)
		close(temp->in);
	if (temp->out != 1)
		close(temp->out);
}

void	run_all(t_cmd *cmd)
{
	char		**env;
	int			i;
	sig_t		sig[2];
	t_cmd		*temp;
	pid_t		*pids;

	//pids = malloc((size_t_command(v->head)) * sizeof(pid_t));
	if (pids == NULL)
		return ;
	temp = cmd;
	env = to_env(g_global.entries, false);
	i = 0;
	sig[0] = signal(SIGINT, sigint_handler_in_process);
	sig[1] = signal(SIGQUIT, sigquit_handler_in_process);
	while (temp)
	{
		run(temp, pids);
		i++;
		temp = temp->next;
	}
	//wait(&);
	while (i >= 1)
		waitpid(pids[i-- - 1], NULL, 0);
	cmd->error = WEXITSTATUS(cmd->error);
	//normal_echo(v);
	signal(SIGINT, sig[0]);
	signal(SIGQUIT, sig[1]);
	//my_clear(&env);
	//correct_echo(v);
}
