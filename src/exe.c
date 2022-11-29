/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:06:19 by acouliba          #+#    #+#             */
/*   Updated: 2022/11/29 17:06:24 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	fix_fd(t_cmd *cmd)
{
	int		in;
	int		out;
	int		error;
	t_file	*file;

	error = 0;
	in = cmd->in;
	out = cmd->out;
	tFile = cmd->file;
	while (tFile)
	{
		if (file->token == INFILE)
			in = infile(file, in, &error);
		else if (file->token == OUTFILE)
			out = outfile(file, out, &error);
		else if (file->token == APPEND)
			out = append_file(file, out, &error);
		else if (file->token == HEREDOC)
			in = here_doc(file, in, &error);
		tFile = file->next;
		if (error)
			break ;
	}
	cmd->error = error;
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
	int		pid[2];

	check_builtin(cmd);
	if (pipe(pid))
	{
		perror("pipe");
		exit(errno);
	}
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd->path != NULL)
		{
			dup2(cmd->in, STDIN_FILENO);
			dup2(cmd->out, STDOUT_FILENO);
			close_all(g_global.cmds);
			if (cmd->error == 0)
				cmd->error = (execve(cmd->path, cmd->cmd, g_global.env));
			put_error(cmd->path, strerror(errno));
			exit(errno);
		}
		exit(cmd->error);
	}
	if (cmd->in != STDIN_FILENO)
		close(cmd->in);
	if (cmd->out != STDOUT_FILENO)
		close(cmd->out);
}

void	fix_all(t_cmd *cmd)
{
	while (cmd)
	{
		fix_fd(cmd);
		cmd = cmd->next;
	}
}

void	exe(t_cmd *cmd)
{
	sig_t		sig[2];

	sig[0] = signal(SIGINT, sigint_handler_in_process);
	sig[1] = signal(SIGQUIT, sigquit_handler_in_process);
	normal_echo();
	my_pipe(cmd);
	fix_all(cmd);
	while (cmd)
	{
		run(cmd);
		cmd = cmd->next;
	}
	cmd = g_global.cmds;
	while (cmd)
	{
		waitpid(cmd->pid, &g_global.exit_code, 0);
		cmd = cmd->next;
	}
	g_global.exit_code = WEXITSTATUS(g_global.exit_code);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sig[1]);
}
