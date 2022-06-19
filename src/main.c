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

int		g_global = 1;

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
	v->pids = malloc((size_t_command(v->head)) * sizeof(pid_t));
	if (v->pids == NULL)
		return ;
	if (v->pids == NULL)
		return ;
	run_all(v);
}

int		main(int ac, char **av, char **env)
{
	char		*str;
	t_var		v;
	int			**pipes;
	t_command	*head;
	char 		**temp_env;

	v.attributes = NULL;
	correct_echo(&v);
	init(env, &v);
	signals(&v);
	str = NULL;
	while (1)
	{
		v.pids = NULL;
		head  = NULL;
		if (str == NULL)
			str = readline(PROMPT_CMD);
		if (str != NULL && ft_strlen(str) == 0)
		{
			free(str);
			str = NULL;
			continue;
		}
		if (str == NULL)
		{
			ft_putstr_fd(PROMPT_CMD, 1);
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		head  = NULL;
		add_history(str);
		temp_env = to_env(v.env, true);
		if (check_quotes(str) && ft_strlen(str))
		{
			head = tokenizer(str);
			v.head = head;
			if (check_redirect(head))
			{
				parser(head, &pipes,env);
				exe(&v);
				cleaning(&head, &pipes, 1);
			}
			else
				cleaning(&head, &pipes, 0);
		}
		free(str);
		str = NULL;
		free(v.pids);
		my_clear(&temp_env);
		//system("leaks minishell");
	}
	return (0);
}
