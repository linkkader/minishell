/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	echo_builtin(t_cmd *cmd)
{
	int		i;
	t_bool	arg;

	i = 1;
	arg = false;
	while (cmd->args[i])
	{
		if (cmd->args[i] && ft_strcmp("-n", cmd->args[i]) == 0)
			arg = true;
		else if (cmd->args[i + 1] == 0)
			ft_putstr_fd(cmd->args[i], cmd->out);
		else
		{
			ft_putstr_fd(cmd->args[i], cmd->out);
			ft_putstr_fd(" ", cmd->out);
		}
		i++;
	}
	if (arg == false)
		ft_putstr_fd("\n", cmd->out);
}
