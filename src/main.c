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
}

static void	exe(t_var *v)
{
	//pid_t	child;
	int		i;

	v->pids = malloc((v->length) * sizeof(pid_t));
	i = -1;
	while (i < v->length)
		v->pids[i++] = -1;
	if (v->pids == NULL)
		return ;
	dup2(v->in, STDIN_FILENO);
	//child = fork();
	//if (child == -1)
	//	perror("Pipe");
	//if (child == 0)
	run_all(v);
	//else
	//wait(NULL);
}

void	init_one(t_var *v, char *str)
{
	v->length = 1;
	v->cmd = malloc(1 * sizeof(char *));
	// tres important
	v->out = dup(STDOUT_FILENO);
	v->console_fd = dup(STDIN_FILENO);
	v->cmd[0] = str;
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		write(1, PROMPT_CMD, ft_strlen(PROMPT_CMD));
	}
	else if (sig == SIGQUIT)
	{

	}
}



int		main(int ac, char **av, char **env)
{
	char				*str;
	t_var				v;
	struct sigaction	sa;

	int			**pipes;
	t_command			*head;

	sigemptyset(&sa.sa_flags);
	sa.sa_handler = &handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	init(env, &v);
	while (1){
		head  = NULL;
		str = readline(PROMPT_CMD);
		if (ft_strlen(str) == 0)
			continue;
		add_history(str);
		head = tokenizer(str);
		if (check_redirect(head))
			parser(head, &pipes,env);
		printf("name %s\n", head->command_name);
		printf("path %s\n", head->command_path);
		int i = 0;
		printf("arg\n");
		while (head->command_args && head->command_args[i]){
			printf("%s ", head->command_args[i++]);
		}
		printf("\n");
		//init_one(&v, str);
		exe(&v);
	}
	return (0);
}
