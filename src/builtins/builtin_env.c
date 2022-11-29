/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	env_builtin(t_cmd *cmd)
{
	t_list	*temp;
	t_entry	*entry;

	if (cmd->cmd[1] == NULL)
	{
		temp = g_global.entries;
		while (temp)
		{
			entry = to_entry(temp->content);
			if (entry->is_exported == true && entry->value != NULL)
			{
				ft_putstr_fd(entry->key, cmd->out);
				ft_putstr_fd("=", cmd->out);
				ft_putstr_fd(entry->value, cmd->out);
				ft_putstr_fd("\n", cmd->out);
			}
			temp = temp->next;
		}
	}
	else
	{
		ft_putstr_fd("env: too many arguments\n", 2);
	}
}
