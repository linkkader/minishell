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

	if (cmd->args[1] == NULL)
	{
		path = getcwd(NULL, 1000);
		if (path == NULL)
		{
			strerror(errno);
			return ;
		}
		ft_putstr_fd(path, cmd->out);
		ft_putstr_fd("\n", cmd->out);
		free(path);
	}
	else
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
	}
}
