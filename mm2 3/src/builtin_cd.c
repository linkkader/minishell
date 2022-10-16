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

#include "../includes/header.h"

static void	part(t_var *v, char *temp, char *path)
{
	temp = getcwd(NULL, 0);
	if (temp != NULL)
		export_value(ft_strdup("OLDPWD"), temp, v, true);
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	path = getcwd(NULL, 0);
	if (path != NULL)
		export_value(ft_strdup("PWD"), path, v, true);
}

void	cd_builtin(char **cmd, t_var *v)
{
	char	*path;
	char	*temp;

	if (v->previous != NULL || v->head->next != NULL)
		return ;
	temp = NULL;
	if (cmd[1] == NULL)
		path = ft_get_env(v, "HOME");
	else if (ft_strncmp("-", cmd[1], ft_strlen(cmd[1])) == 0)
	{
		path = ft_get_env(v, "OLDPWD");
		if (path == NULL)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", v->console_fd);
			return ;
		}
	}
	else
		path = cmd[1];
	if (access(path, X_OK) == 0)
		part(v, temp, path);
	else
		perror("cd");
}
