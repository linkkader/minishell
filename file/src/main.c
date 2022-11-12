/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:55:30 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/22 10:03:00 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

	add_history(str);
	head = NULL;
	pipes = NULL;
	temp_env = to_env(v->env, true);
	if (check_quotes(str) && ft_strlen(str))
	{
		head = tokenizer(str);
		v->head = head;
		g_global.error = v->err;
		if (check_redirect(head))
		{
			parser(head, &pipes, temp_env);
			if (g_global.heredoc_exit != 99)
				run_all(v);
			cleaning(&head, &pipes, 1);
		}
		else
			cleaning(&head, &pipes, 0);
	}
	free(str);
	my_clear(&temp_env);
}

static void	*prompt(void)
{
	g_global.heredoc_exit = 1;
	return (readline(PROMPT_CMD));
}


int	main(int ac, char **av, char **env)
{
	char		*str;
	t_var		v;

	if (ac != 1 && av[1])
		return (write(2, "too many arguments!", 19));
	init(env, &v, &str);
	while (1)
	{
		str = prompt();
		if (str != NULL && ft_strlen(str) == 0)
		{
			free(str);
			str = NULL;
			continue ;
		}
		if (str == NULL)
		{
			reset_setting(&v);
			ft_putstr_fd(PROMPT_CMD, 1);
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		exe(&v, str);
	}
	return (0);
}
