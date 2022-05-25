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

static int	path_index(char **env)
{
	int		i;

	i = 0;
	while (1)
	{
		if (ft_strncmp ("PATH=/", env[i], 6) == 0)
			break ;
		if (env[i] == NULL)
		{
			i = -1;
			break ;
		}
		i++;
	}
	return (i);
}

static void	init(char **env, t_var *var, int ac, char **av)
{
	int		index;

	index = path_index(env);
	if (index == -1)
		return ;
	var->sp = ft_split(env[index], ':');
	var->env = env;
}

static void	exe(t_var v)
{
	pid_t	child;
	int		i;

	v.pids = malloc((v.length) * sizeof(pid_t));
	i = -1;
	while (i < v.length)
		v.pids[i++] = -1;
	if (v.pids == NULL)
		return ;
	dup2(v.in, STDIN_FILENO);
	child = fork();
	chdir("/");
	if (child == -1)
		perror("Pipe");
	if (child == 0)
		run_all(&v);
	else
		wait(NULL);
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

int		main(int ac, char **av, char **env)
{
	char 	*str;
	t_var	v;

	init(env, &v, ac, av);
	while (1){
		str = readline("minishell$ ");
		add_history(str);
		init_one(&v, str);
		exe(v);
	}
	return (0);
}