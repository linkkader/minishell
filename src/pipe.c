//
// Created by Abdoul Kader on 13/11/2022.
//

#include "../includes/header.h"

void	my_pipe(t_cmd *cmd)
{
	int		fd[2];
	int		nextIn;


	nextIn = dup(STDIN_FILENO);
	while (cmd)
	{
		if (cmd->next == NULL)
		{
			cmd->out = dup(STDOUT_FILENO);
			cmd->in = nextIn;
		}
		else
		{
			cmd->in = nextIn;
			pipe(fd);
			// printf("fd[0] = %d  fd[1] = %d\n",	fd[0], fd[1]);
			cmd->out = fd[1];
			nextIn = fd[0];
		}
		cmd = cmd->next;
	}
}
