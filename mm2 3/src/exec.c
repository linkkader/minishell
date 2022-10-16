/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/22 11:27:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**check_builtin(t_command *head, t_var *var)
{
	char	*name;
	int		len;

	name = head->cmd;
	len = ft_strlen(name) + 1;
	if (ft_strncmp(name, "exit", len) == 0)
		exit_builtin(head->args, var);
	else if (ft_strncmp(name, "unset", ft_strlen(name)) == 0)
		unset_builtin(head->args, var);
	else if (ft_strncmp(name, "export", len) == 0)
		export_builtin(head->args, var);
	else if (ft_strncmp(name, "cd", len) == 0)
		cd_builtin(head->args, var);
	else if (ft_strncmp(name, "pwd", len) == 0)
		pwd_builtin(head->args, var);
	else if (ft_strncmp(name, "env", len) == 0)
		env_builtin(head->args, var);
	else if (ft_strncmp(name, "echo", len) == 0)
		echo_builtin(head->args, var);
	else
		return (head->args);
	return (NULL);
}

char	**check_cmd(t_var *v, t_command *head)
{
	char	**sp;

	if (head == NULL || head->cmd == NULL)
		return (NULL);
	sp = head->args;
	if (sp == NULL)
		return (NULL);
	if (check_builtin(head, v) == NULL)
		return (NULL);
	if (head->path)
		return (head->args);
	try_export_value(sp, v, false, 0);
	return (NULL);
}
