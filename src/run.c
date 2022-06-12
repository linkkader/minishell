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

static pid_t	run(char *path, char **arg, t_var *v, t_command *cmd, int in, int *out)
{
	int		pdes[2];
	pid_t	child;

	//if (next_cmd)
	//{
	//	printf("ok\n");
		//next_cmd->output = dup(pdes[1]);//read here but pipe input
		//next_cmd->input = dup(pdes[0]);//write here but pipe output
	//}
	pipe(pdes);
	child = fork();
	if (child == -1)
		perror("Pipe");
	else if (child == 0)
	{
		if (cmd->next)
			dup2(pdes[1], STDOUT_FILENO);
		else
			dup2(v->out, STDOUT_FILENO);
		dup2(in, STDIN_FILENO);

		//dup2(pdes[1], STDOUT_FILENO);
		close(pdes[0]);
		execve(path, arg, NULL);
		exit(0);
	}
	wait(NULL);


	close(pdes[1]);
	cmd->output = dup(pdes[0]);

	return child;
//	while (read(dup(*out), &c, 1) > 0)
//		write(1, &c, 1);
//	printf("end\n");
//	while (1);




//	close(pdes[1]);
//	//close(pdes[0]);
//	if(next_cmd){
//		printf("here");
//		close(next_cmd->input);
//	}
//	//if (next_cmd->next)next_cmd->next->input = pdes[0];
//	//printf("out %d %d in\n", v->out, v->in);
//	return (child);
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
	//close(pdes[1]);
	return (id);
	///dup2(pdes[0], STDIN_FILENO);
}

void	run_all(t_var *v)
{
	t_command	*temp;
	char		**args;
	char		*path;
	int 		i;
	int		pdes[2];

	int 	fd;

	fd = open("MAKEFILE", O_RDONLY);
	int outfd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	v->in = dup(fd);
	v->out = dup(0);
	//need optimize
	i = 0;
	//dup2(v->out, STDOUT_FILENO);

	//temp = v->head;
	//while (temp && temp->next){
	//	temp = temp->next;
	//}
	temp = v->head;
	int in = v->in;
//	if (temp && 0)
//	{
//		args = check_cmd(v, temp, &path);
//		v->pids[i] = run(path, args, v, temp->next, v->in, &v->out);
//		in = v->out;
//		i++;
//		//temp->output = v->out;
//		temp = temp->next;
//	}
	while (temp)
	{
		args = check_cmd(v, temp, &path);
		if (args != NULL)
		{
			v->pids[i] = run(path, args, v, temp, in, &v->out);
			in = temp->output;
		}
		temp = temp->next;
		i++;
	}
	//args = check_cmd(v, temp, &path);
	//if (args != NULL)
	//	v->pids[i] = run_last(v, path, args);
	while (i > -1)
		waitpid(v->pids[i--], NULL, 0);

}
