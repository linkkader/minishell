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

void	not_an_identifier(char *error)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

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
		if (value == NULL)
			return (true);
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

//[a-zA-Z_][a-zA-Z0-9_]
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
		part1(key, value, is_in_export);
	system("leaks minishell");
	update_env();
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

static	char *get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}

static char	*get_value(char *str)
{
	int		i;
	char	*value;
	char	*temp;
	char	*sub;

	temp = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			temp = ft_get_env(get_key(str));
		}
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	sub = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (temp == NULL)
		value = sub;
	else
	{
		value = ft_strjoin(temp, sub);
		free(temp);
		free(sub);
	}
	return (value);
}

//[a-zA-Z_][a-zA-Z0-9_]
void	try_export(char *str, t_cmd *cmd)
{
	int		i;

	if (!(ft_isalpha(str[0]) == 1 || str[0] == '_'))
	{
		not_an_identifier(str);
		return ;
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break;
		if (!(ft_isalpha(str[i]) == 1 || ft_isalnum(str[i]) == 1 || str[i] == '_'))
		{
			not_an_identifier(str);
			return ;
		}
		i++;
	}
	export_value(get_key(str),
				 get_value(str),cmd,
				 true);
}

void	export_builtin(t_cmd *cmd)
{
	t_list	*temp;
	t_entry	*entry;
	int 	i;

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
	else {
		while (cmd->cmd[i] != NULL)
		{
			try_export(cmd->cmd[i], cmd);
			i++;
		}
	}
}
