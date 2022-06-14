/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:55:30 by acouliba          #+#    #+#             */
/*   Updated: 2022/05/24 14:55:39 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init(char **env, t_var *var)
{
	int		index;

	index = 0;
	var->env = NULL;
	while (env[index])
	{
		push(&var->env, env[index]);
		index++;
	}
	//var->length = 1000;
	//v->out = dup(STDOUT_FILENO);
	var->console_fd = 2;
}

static int size_t_command(t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

static void	exe(t_var *v)
{
	int		i;

	v->pids = malloc((size_t_command(v->head)) * sizeof(pid_t));
	if (v->pids == NULL)
	{
		//exit here
	}
	i = -1;
	if (v->pids == NULL)
		return ;
	run_all(v);
	wait(NULL);
}


void correct_echo()
{
	struct termios attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~~(ECHO | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

int		main(int ac, char **av, char **env)
{
	//return test(ac, av, env);
	char		*str;
	t_var		v;
	int			**pipes;
	t_command	*head;
	char 		**temp_env;

	int 	i = 0;

	signals();
	correct_echo();
	init(env, &v);
	while (1)
	{
		v.pids = NULL;
		i++;
		str = readline(PROMPT_CMD);
		if (str == NULL)
		{
			ft_putstr_fd(PROMPT_CMD, 1);
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		head  = NULL;
		add_history(str);
		head = tokenizer(str);
		temp_env = to_env(v.env);
		if (check_redirect(head))
			parser(head, &pipes, temp_env);
		v.head = head;
		t_command *temp = head;
		while (temp)
		{
			printf("%s  %d %d\n", temp->command_name, temp->input, temp->output);
			temp = temp->next;
		}
		free(v.pids);
		exe(&v);
		free(str);
		my_clear(temp_env);
		//cleaning(&head, &pipes);
	}
	return (0);
}
