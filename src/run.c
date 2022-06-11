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

static void clear_pipe(int fd)
{
	char	c;

	while (read(fd, &c, 1))
	{
	}
}

static void	my_clear(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
}

static pid_t	run(char *path, char **arg)
{
	int		pdes[2];
	pid_t	child;

	pipe(pdes);
	child = fork();
	if (child == -1)
		perror("Pipe");
	else if (child == 0)
	{
		printf("path run %s\n", path);
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[0]);
		execve(path, arg, NULL);
		exit(0);
	}
	close(pdes[1]);
	//dup2(pdes[0], STDIN_FILENO);
	close(pdes[0]);
	return (child);
}

static int	run_last(t_var *v, char *path, char **arg)
{
	int		pdes[2];
	pid_t	id;

	pipe(pdes);
	id = fork();
	if (id == -1)
		perror("Pipe");
	else if (id == 0)
	{
		printf("path %s\n", path);
		dup2(pdes[1], v->out);
		close(pdes[0]);
		execve(path, arg, NULL);
		exit(0);
	}
	close(pdes[1]);
	return (id);
	///dup2(pdes[0], STDIN_FILENO);
}

void	run_all(t_var *v)
{
	t_command	*temp;
	char		**args;
	char		*path;
	int 		i;

	//need optimize
	i = 0;
	dup2(v->out, STDOUT_FILENO);
	temp = v->head;
	while (temp && temp->next)
	{
		args = check_cmd(v, temp, &path);
		if (args != NULL)
			run(path, args);
		else
			clear_pipe(STDIN_FILENO);
		temp = temp->next;
		i++;
	}
	args = check_cmd(v, temp, &path);
	if (args != NULL)
		v->pids[i] = run_last(v, path, args);
	while (i > -1)
		waitpid(v->pids[i--], NULL, 0);
}
