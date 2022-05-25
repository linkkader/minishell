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

#include "pipex.h"

static void	clear_pipe(int fd)
{
	char	c;

	while (read(fd, &c, 1))
	{
	}
}

static void	clear(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
}

static pid_t	run(char **cmd)
{
	int		pdes[2];
	pid_t	child;

	pipe(pdes);
	child = fork();
	if (child == -1)
		perror("Pipe");
	else if (child == 0)
	{
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[0]);
		execve(cmd[0], cmd, NULL);
		exit(1);
	}
	close(pdes[1]);
	dup2(pdes[0], STDIN_FILENO);
	close(pdes[0]);
	clear(cmd);
	return (child);
}

static void	run_last(char **cmd, t_var *v, int i)
{
	int		pdes[2];

	pipe(pdes);
	v->pids[i] = fork();
	if (v->pids[i] == -1)
		perror("Pipe");
	else if (v->pids[i] == 0)
	{
		dup2(pdes[1], v->out);
		close(pdes[0]);
		execve(cmd[0], cmd, NULL);
		exit(0);
	}
	close(pdes[1]);
	dup2(pdes[0], STDIN_FILENO);
}

void	run_all(int length, t_var *v, int start, int console_fd)
{
	int		i;
	char	**cmd;

	i = 0;
	dup2(v->out, STDOUT_FILENO);
	while (i < length - 2)
	{
		cmd = check_cmd(*v, i + start, console_fd);
		if (cmd != NULL)
		{
			v->pids[i] = run(cmd);
		}
		else
			clear_pipe(STDIN_FILENO);
		i++;
	}
	cmd = check_cmd(*v, i + start, console_fd);
	if (cmd != NULL)
		run_last(cmd, v, i);
	else
		clear_pipe(STDIN_FILENO);
	while (i > -1)
		waitpid(v->pids[i--], NULL, 0);
	exit(1);
}
