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

extern int	g_global;

extern int g_errno;

static void	init(char **env, t_var *var, char **str)
{
	int		index;

	var->attributes = NULL;
	str[0] = NULL;
	correct_echo(var);
	index = 0;
	var->env = NULL;
	var->err = 0;
	signals(var);
	while (env[index])
	{
		push(&var->env, env[index]);
		index++;
	}
	var->console_fd = 2;
}

static void	exe(t_var *v, char *str)
{
	int			**pipes;
	t_command	*head;
	char		**temp_env;

	v->pids = malloc((size_t_command(v->head)) * sizeof(pid_t));
	if (v->pids == NULL)
		return ;
	add_history(str);
	head = NULL;
	pipes = NULL;
	temp_env = to_env(v->env, true);
	g_errno = v->err;
	if (check_quotes(str) && ft_strlen(str))
	{
		head = tokenizer(str);
		v->head = head;
		if (check_redirect(head))
		{
			parser(head, &pipes, temp_env);
			if (g_global != -1)
				run_all(v);
			cleaning(&head, &pipes, 1);
		}
		else
			cleaning(&head, &pipes, 0);
	}
	free(str);
	free(v->pids);
	my_clear(&temp_env);
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_var		v;

	g_errno = 0;
	init(env, &v, &str);
	while (1)
	{
		g_global = 1;
		str = readline(PROMPT_CMD);
		if (str != NULL && ft_strlen(str) == 0)
		{
			free(str);
			str = NULL;
			continue ;
		}
		if (str == NULL)
		{
			ft_putstr_fd(PROMPT_CMD, 1);
			ft_putstr_fd("exit\n", 1);
			reset_setting(&v);
			exit(0);
		}
		exe(&v, str);
	}
	return (0);
}
