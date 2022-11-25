/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void	part(t_cmd *cmd, char *path)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (temp != NULL)
		export_value(ft_strdup("OLDPWD"), temp, cmd, true);
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	path = getcwd(NULL, 0);
	if (path != NULL)
		export_value(ft_strdup("PWD"), path, cmd, true);
}

void	cd_builtin(t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (cmd->cmd[1] == NULL || ( cmd->cmd[1] != NULL && ft_strcmp(cmd->cmd[1], "~") == 0))
		path = ft_get_env("HOME");
	else if (ft_strcmp("-", cmd->cmd[1]) == 0)
	{
		path = ft_get_env("OLDPWD");
		if (path == NULL)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			free(path);
			return ;
		}
	}
	else
		path = ft_strdup(cmd->cmd[1]);
	if (access(path, X_OK) == 0)
		part(cmd, path);
	else
		perror("cd");
	free(path);
}
