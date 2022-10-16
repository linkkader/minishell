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
//	while (tmp)
//	{
//		check_builtin(tmp);
//		printf("path %s\n", tmp->path);
//		tmp = tmp->next;
//	}
	//while (1);
}

char	**check_cmd(t_cmd *tmp)
{
	//try_export_value(sp, v, false, 0);
	return (NULL);
}