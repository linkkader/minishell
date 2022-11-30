/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	not_an_identifier(char *error, t_cmd *cmd)
{
	cmd->error = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static void	export_print(t_cmd *cmd, t_entry *entry)
{
	ft_putstr_fd("declare -x ", cmd->out);
	ft_putstr_fd(entry->key, cmd->out);
	if (entry->is_exported == true && entry->value != NULL)
	{
		ft_putstr_fd("=\"", cmd->out);
		ft_putstr_fd(entry->value, cmd->out);
		ft_putstr_fd("\"", cmd->out);
	}
	ft_putstr_fd("\n", cmd->out);
}

//[a-zA-Z_][a-zA-Z0-9_]
void	try_export(char *str, t_cmd *cmd)
{
	int		i;

	if (!(ft_isalpha(str[0]) == 1 || str[0] == '_'))
	{
		not_an_identifier(str, cmd);
		return ;
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!(ft_isalpha(str[i]) == 1
				|| ft_isalnum(str[i]) == 1 || str[i] == '_'))
		{
			not_an_identifier(str, cmd);
			return ;
		}
		i++;
	}
	export_value(get_key_cmd(str),
		get_value_cmd(str), cmd,
		true);
}

void	export_builtin(t_cmd *cmd)
{
	t_list	*temp;
	t_entry	*entry;
	int		i;

	i = 1;
	if (cmd->cmd[1] == NULL)
	{
		temp = g_global.entries;
		while (temp)
		{
			entry = to_entry(temp->content);
			if (entry->is_exported == true)
				export_print(cmd, entry);
			temp = temp->next;
		}
	}
	else
	{
		while (cmd->cmd[i] != NULL)
		{
			try_export(cmd->cmd[i], cmd);
			i++;
		}
	}
}

char	*get_key_cmd(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}
