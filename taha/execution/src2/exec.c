//
// Created by Abdoul Kader on 9/10/2022.
//

#include "../../minishell.h"

void	exec_kader(t_cmd *tmp, int *pid, int i)
{
	t_cmd	*temp;

	temp = tmp;
	while (tmp)
	{
		check_builtin(tmp);
		tmp = tmp->next;
	}
	//while (1);
}

char	**check_cmd(t_cmd *tmp)
{
	//try_export_value(sp, v, false, 0);
	return (NULL);
}