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
		close(pdes[0]);
		execve(path, arg, NULL);
		exit(0);
	}


	close(pdes[1]);
	cmd->output = dup(pdes[0]);

	return child;
}

static pid_t	run_null(char *path, char **arg, t_var *v, t_command *cmd, int in, int *out)
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
	close(pdes[1]);
	char c;
	while (read(in, &c, 1))
	{
		write(pdes[1], &c, 1);
	}
	//write(1, "enf\n", 4);
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


void	exe(t_command *tmp, char **env)
{
	int	id;

	while (tmp)
	{
		id = fork();
		if (!id)
		{
			dup2(tmp->input, 0);
			dup2(tmp->output, 1);
			if (tmp->input != 0)
				close(tmp->input);
			if (tmp->output != 1)
				close(tmp->output);
			if (tmp->should_execute)
				if (execve(tmp->command_path, tmp->command_args, env) == -1)
					exit (1/*puterror("", strerror(errno))*/);
			exit (2);
		}
		wait(NULL);
		if (tmp->input != 0)
			close(tmp->input);
		if (tmp->output != 1)
			close(tmp->output);
		tmp = tmp->next;
	}
}


void	run_all(t_var *v)
{
	t_command	*temp;
	char		**args;
	char		*path;
	int 		i;
	int		pdes[2];

	int 	fd;

	temp = v->head;
	i = 0;
	while (temp)
	{
		v->out = temp->output;
		args = check_cmd(v, temp, &path);
		if (args != NULL)
		{
			v->pids[i] = fork();
			if (!v->pids[i])
			{
				dup2(temp->input, 0);
				dup2(temp->output, 1);
				if (temp->input != 0)
					close(temp->input);
				if (temp->output != 1)
					close(temp->output);
				if (temp->should_execute)
					if (execve(temp->command_path, temp->command_args, NULL) == -1)
						exit (1/*puterror("", strerror(errno))*/);
				exit (2);
			}
		}
		if (temp->input != 0)
			close(temp->input);
		if (temp->output != 1)
			close(temp->output);
		//tmp = tmp->next;
		i++;
		temp = temp->next;
	}
	while (i > -1)
		waitpid(v->pids[i--], NULL, 0);
	//while (1);
}


void	run_all1(t_var *v)
{
	t_command	*temp;
	char		**args;
	char		*path;
	int 		i;
	int		pdes[2];

	int 	fd;

	fd = open("MAKEFILE", O_RDONLY);
	int outfd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	//v->in = dup(fd);
	v->in = dup(v->head->input);
	v->out = dup(0);
	//need optimize
	i = 0;
	v->head->input = v->in;
	temp = v->head;
	int in = v->in;
	while (temp)
	{
		args = check_cmd(v, temp, &path);
		if (args != NULL)
		{
			v->pids[i] = run(path, args, v, temp, temp->input, &v->out);
			if (temp->next)
				temp->next->input = temp->output;
		}
		else
		{
			temp->next->input = to_pipe(temp->input);
		}
		temp = temp->next;
		i++;
	}
	while (i > -1)
		waitpid(v->pids[i--], NULL, 0);

}
