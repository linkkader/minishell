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
	int		i;

	if (v->pids == NULL)v->pids = malloc((v->length) * sizeof(pid_t));
	i = -1;
	if (v->pids == NULL)
		return ;
	while (i < v->length)
		v->pids[i++] = -1;
	run_all(v);
	wait(NULL);
}

void	init_one(t_var *v, char *str)
{
	v->length = 1000;
	v->out = dup(STDOUT_FILENO);
	v->console_fd = dup(STDIN_FILENO);
}


void disable_echo()
{
	struct termios attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~~(ECHO | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

int		main(int ac, char **av, char **env)
{
	char				*str;
	t_var				v;
	int			**pipes;
	t_command			*head;

	signals();
	disable_echo();
	init(env, &v);
	int i = 0;

	v.pids = NULL;
	v.fake = NULL;

	while (1){
		i++;
		str = readline(PROMPT_CMD);
		if (str == NULL){
			ft_putstr_fd("NULL\n", 2);
			exit(0);
		}
		head  = NULL;
		add_history(str);
		head = tokenizer(str);
		if (check_redirect(head))
			parser(head, &pipes,env);
		init_one(&v, str);
		v.head = head;
		t_command *temp = head;
		while (temp)
		{
			printf("%s  %d %d\n", temp->command_name, temp->input, temp->output);
			temp = temp->next;
		}
		exe(&v);
		str = NULL;
	}
	return (0);
}
