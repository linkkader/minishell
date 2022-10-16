/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	part(t_cmd *cmd, char *temp, char *path)
{
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
	char	*temp;

	temp = NULL;
	path = NULL;
	if (cmd->args[1] == NULL)
		path = ft_get_env(cmd, "HOME");
	else if (ft_strcmp("-", cmd->args[1]) == 0)
	{
		path = ft_get_env(cmd, "OLDPWD");
		if (path == NULL)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return ;
		}
	}
	else
		path = cmd->args[1];
	if (access(path, X_OK) == 0)
		part(cmd, temp, path);
	else
		perror("cd");
}
