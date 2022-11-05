/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static t_bool	part(t_list *temp, char *key,
					char *value, t_bool is_in_export)
{
	t_entry	*entry;

	entry = to_entry(temp->content);
	if (ft_strncmp(key, entry->key, ft_strlen(entry->key) + 1) == 0)
	{
		free(key);
		if (value == NULL && entry->value != NULL)
			entry->is_exported = is_in_export;
		if (entry->value)
			free(entry->value);
		entry->value = value;
		return (true);
	}
	return (false);
}

static void	part1(char *key, char *value, t_bool is_in_export)
{
	t_entry	*entry;

	entry = malloc(sizeof(*entry));
	if (entry == NULL)
		return ;
	entry->key = key;
	entry->is_exported = is_in_export;
	entry->value = value;
	ft_lstadd_back(&g_global.entries, ft_lstnew(entry));
}

void	export_value(char *key, char *value, t_cmd *cmd,
			t_bool is_in_export)
{
	t_list	*temp;
	t_bool	is_in;

	if (key == NULL)
		return ;
	is_in = false;
	temp = g_global.entries;
	while (temp)
	{
		is_in = part(temp, key, value, is_in_export);
		if (is_in == true)
			break ;
		temp = temp->next;
	}
	if (is_in == false)
		part1( key, value, is_in_export);
	free_2d(g_global.env);
	g_global.env = to_env(g_global.entries, true);
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

void	export_builtin(t_cmd *cmd)
{
	t_list	*temp;
	t_entry	*entry;

	if (cmd->args[1] == NULL)
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
}
