/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_bool	is_option(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (false);
    i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	echo_builtin(t_cmd *cmd)
{
	int		i;
	t_bool	arg;
	t_bool	ignore;

	i = 1;
	arg = false;
	ignore = false;
	ft_putstr_fd("echo\n", 1);
	while (cmd->cmd[i])
	{
		if (ignore == false && cmd->cmd[i] && is_option(cmd->cmd[i]))
			arg = true;
		else if (cmd->cmd[i + 1] == 0)
		{
			ft_putstr_fd(cmd->cmd[i], cmd->out);
		}
		else
		{
			ft_putstr_fd(cmd->cmd[i], cmd->out);
			ft_putstr_fd(" ", cmd->out);
			ignore = true;
		}
		i++;
	}
	if (arg == false)
		ft_putstr_fd("\n", cmd->out);
}
