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
		close(temp->out);
	return (execve(temp->path, temp->args, g_global.env));
	exit (2);
}

static void	run(t_cmd *temp, pid_t *pids, int *i)
{
	//check if builtin
	check_builtin(temp);
	printf("path = %s\n", temp->path);
	pids[*i] = fork();
	if (pids[*i] == 0)
		temp->error = exe(temp);
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
//	sig[0] = signal(SIGINT, sigint_handler_in_process);
//	sig[1] = signal(SIGQUIT, sigquit_handler_in_process);
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
		printf(" = %d\n", i);
		waitpid(pids[i], NULL, 0);
	}
	g_global.exit_code = WEXITSTATUS(g_global.exit_code);
	//normal_echo(v);
//	signal(SIGINT, sig[0]);
//	signal(SIGQUIT, sig[1]);
	//my_clear(&env);
	//correct_echo(v);
}
