//
// Created by Abdoul Kader on 9/10/2022.
//

#include "../../minishell.h"

void	exec_kader(t_cmd *cmd, int *pid, int i)
{
	t_cmd	*tmp;

	pid = malloc(list_size(cmd) * sizeof(int));
	if (pid == NULL)
		return ;
	tmp = cmd;
	run_all(cmd, pid);
}
