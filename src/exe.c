//
// Created by Abdoul Kader on 12/11/2022.
//

#include "../includes/header.h"

int 	infile(t_cmd *cmd)
{
	int		i;
	int 	fd;

	fd = -1;
	i = 0;
	while (cmd->infile[i])
	{
		fd = open(cmd->infile[i], O_RDONLY);
		if (fd < 0)
		{
			perror("minishell");
			break ;
		}
		i++;
	}
	return (fd);
}

int		outfile(t_cmd *cmd)
{
	int		i;
	int 	fd;

	fd = -1;
	i = 0;
	while (cmd->outfile[i])
	{
		fd = open(cmd->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("minishell");
			break ;
		}
		i++;
	}
	return (fd);
}

void	close_all(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->in != 0)
			close(cmd->in);
		if (cmd->out != 1)
			close(cmd->out);
		cmd = cmd->next;
	}
}

void	run(t_cmd *cmd)
{
	int 	in;
	int 	out;
	int 	pid[2];

	check_builtin(cmd);
	if (pipe(pid))
	{
		perror("minishell");
		exit(errno);
	}
	printf(" ok \n");
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd->path != NULL)
		{
			dup2(cmd->in, STDIN_FILENO);
			dup2(cmd->out, STDOUT_FILENO);
			(execve(cmd->path, cmd->args, g_global.env));
		}
		//todo: need to exit with the exit code of the command
		exit(0);
	}
	if (cmd->in != STDIN_FILENO)
		close(cmd->in);
	if (cmd->out != STDOUT_FILENO)
		close(cmd->out);
}

void	exe(t_cmd *cmd)
{
	sig_t		sig[2];

	sig[0] = signal(SIGINT, sigint_handler_in_process);
	sig[1] = signal(SIGQUIT, sigquit_handler_in_process);
	my_pipe(cmd);
	while (cmd)
	{
		run(cmd);
		waitpid(cmd->pid, &g_global.exit_code, 0);
		cmd = cmd->next;
	}
	cmd = g_global.cmds;
	while (cmd)
	{
		waitpid(cmd->pid, &g_global.exit_code, 0);
		cmd = cmd->next;
	}
	g_global.exit_code = WEXITSTATUS(g_global.exit_code);
	signal(SIGINT, sig[0]);
	signal(SIGQUIT, sig[1]);
}