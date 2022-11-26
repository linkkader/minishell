//
// Created by Abdoul Kader on 12/11/2022.
//

#include "../includes/header.h"

void	fix_fd(t_cmd *cmd)
{
	int 	in;
	int 	out;
	int		error;
	t_file	*tFile;

	error = 0;
	in = cmd->in;
	out = cmd->out;
	tFile = cmd->file;
	while (tFile)
	{
		if (tFile->token == INFILE)
			in = infile(tFile, in, &error);
		else if (tFile->token == OUTFILE)
			out = outfile(tFile, out, &error);
		else if (tFile->token == APPEND)
			out = append_file(tFile, out, &error);
		else if (tFile->token == HEREDOC)
			in = here_doc(tFile, in, &error);
		tFile = tFile->next;
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
	int 	pid[2];

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
			ft_putstr_fd("minishell error : ", 2);
			ft_putnbr_fd(cmd->error, 2);
			ft_putstr_fd("\n", 2);
			exit(cmd->error);
		}
		exit(cmd->error);
	}
	if (cmd->in != STDIN_FILENO)
		close(cmd->in);
	if (cmd->out != STDOUT_FILENO)
		close(cmd->out);
}

void    fix_all(t_cmd *cmd)
{
    while (cmd)
    {
        fix_fd(cmd);
        // printf("cmd->in = %d cmd->out = %d\n", cmd->in, cmd->out);
        // run(cmd);
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
//		fix_fd(cmd);
		// printf("cmd->in = %d cmd->out = %d\n", cmd->in, cmd->out);
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
	printf("exit code = %d\n", g_global.exit_code);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sig[1]);
}