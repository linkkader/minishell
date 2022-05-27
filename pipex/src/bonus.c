/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:08:38 by acouliba          #+#    #+#             */
/*   Updated: 2022/03/06 10:08:58 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	my_pipe(int length, t_var v, int start)
{
	//pid_t	child;
	int		console_fd;
	int		i;

	v.pids = malloc((length - 2) * sizeof(pid_t));
	i = -1;
	while (i < length)
		v.pids[i++] = -1;
	if (v.pids == NULL)
		return ;
	console_fd = dup(STDIN_FILENO);
	dup2(v.in, STDIN_FILENO);
	//child = fork();
	//if (child == -1)
	//	perror("Pipe");
	//if (child == 0)
	run_all(length, &v, start, console_fd);
	//else
	wait(NULL);
}

void	doc_here(t_var v)
{
	pid_t	child;
	char	*limit;
	int		pdes[2];

	limit = v.av[2];
	pipe(pdes);
	child = fork();
	if (child == -1)
		perror("Pipe");
	else if (child == 0)
		exec_doc(pdes, limit);
	wait(NULL);
	close(pdes[1]);
	v.in = dup(to_pipe(dup(pdes[0])));
	my_pipe(v.ac - 3, v, 3);
}

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
	int		outfd;

	index = path_index(env);
	if (index == -1)
		return ;
	var->sp = ft_split(env[index], ':');
	var->av = av;
	var->ac = ac;
	var->env = env;
	outfd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfd == -1)
		perror(av[ac - 1]);
	var->out = dup(outfd);
}
//outfd = 1;

int	main(int ac, char **av, char **env)
{
	t_var	v;
	int		fd;

	if (ac >= 5)
	{
		init(env, &v, ac, av);
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			doc_here(v);
		else
		{
			fd = open(av[1], O_RDONLY);
			if (access(av[1], F_OK) != 0)
			{
				perror(av[1]);
				v.in = to_pipe(dup(fd));
			}
			else
				v.in = dup(fd);
			my_pipe(ac - 2, v, 2);
		}
	}
	else
		ft_printf("Invalid arguments");
	return (1);
}
