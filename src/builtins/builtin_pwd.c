/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	pwd_builtin(t_cmd *cmd)
{
	char	*path;

	if (cmd->cmd[1] == NULL)
	{
		path = getcwd(NULL, 1000);
		if (path == NULL)
			path = ft_get_env("PWD");
		if (path == NULL)
		{
			ft_putstr_fd("minishell: pwd: PWD not set\n", 2);
			return ;
		}
		ft_putstr_fd(path, cmd->out);
		ft_putstr_fd("\n", cmd->out);
		free(path);
	}
	else
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		cmd->error = 1;
	}
}
