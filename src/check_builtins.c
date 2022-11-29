/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/22 11:27:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	part(t_cmd *tmp, char *name)
{
	if (ft_strcmp(name, "cd") == 0)
		cd_builtin(tmp);
	else if (ft_strcmp(name, "echo") == 0)
		echo_builtin(tmp);
	else if (ft_strcmp(name, "exit") == 0)
		exit_builtin(tmp);
	else if (ft_strcmp(name, "pwd") == 0)
		pwd_builtin(tmp);
	else if (ft_strcmp(name, "export") == 0)
		export_builtin(tmp);
	else if (ft_strcmp(name, "unset") == 0)
		unset_builtin(tmp);
	else if (ft_strcmp(name, "env") == 0)
		env_builtin(tmp);
	else
	{
		tmp->path = get_cmd_path(tmp,
				tmp->cmd[0]);
	}
}

void	check_builtin(t_cmd *tmp)
{
	char	*name;

	tmp->path = NULL;
	if (tmp->cmd == NULL)
		return ;
	name = ft_strdup(tmp->cmd[0]);
	part(tmp, name);
	free(name);
}
