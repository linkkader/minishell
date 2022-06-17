/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/17 20:09:36 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run(t_var *v, t_command *temp, int *i, char **env)
{
	char	**args;

	v->out = temp->output;
	args = check_cmd(v, temp);
	if (args != NULL)
	{
		v->pids[*i] = fork();
		if (!v->pids[*i])
		{
			dup2(temp->input, 0);
			dup2(temp->output, 1);
			if (temp->input != 0)
				close(temp->input);
			if (temp->output != 1)
				close(temp->output);
			if (temp->should_execute)
				if (execve(temp->command_path, temp->command_args, env) == -1)
					exit (1);
			exit (2);
		}
	}
	if (temp->input != 0)
		close(temp->input);
	if (temp->output != 1)
		close(temp->output);
}

void	run_all(t_var *v)
{
	t_command	*temp;
	char		**env;
	int			i;
	sig_t		sig[2];

	temp = v->head;
	env = to_env(v->env);
	i = 0;
	v->sig_int = signal(SIGINT, sigint_handler_in_process);
	v->sig_quit = signal(SIGQUIT, sigquit_handler_in_process);
	normal_echo(v);
	while (temp)
	{
		run(v, temp, &i, env);
		i++;
		temp = temp->next;
	}
	while (i > -1)
		waitpid(v->pids[i--], NULL, 0);
	my_clear(&env);
	signal(SIGINT, v->sig_int);
	signal(SIGQUIT, v->sig_quit);
	correct_echo(v);
}
