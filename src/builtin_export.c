/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/05/25 15:45:03 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	part1(t_var *var, char *key, char *value, t_bool is_in_export)
{
	t_entry	*entry;

	entry = malloc(sizeof(*entry));
	if (entry == NULL)
		return ;
	entry->key = key;
	entry->is_exported = is_in_export;
	entry->value = value;
	ft_lstadd_back(&var->env, ft_lstnew(entry));
}

void	export_value(char *key, char *value, t_var *var,
			t_bool is_in_export)
{
	t_list	*temp;
	t_bool	is_in;

	if (var->previous != NULL || var->head->next != NULL)
		return ;
	if (key == NULL)
		exit_builtin(var);
	is_in = false;
	temp = var->env;
	while (temp)
	{
		is_in = part(temp, key, value, is_in_export);
		if (is_in == true)
			break ;
		temp = temp->next;
	}
	if (is_in == false)
		part1(var, key, value, is_in_export);
}

static void	export_print(t_var *v, t_entry *entry)
{
	ft_putstr_fd("declare -x ", v->out);
	ft_putstr_fd(entry->key, v->out);
	if (entry->is_exported == true && entry->value != NULL)
	{
		ft_putstr_fd("=\"", v->out);
		ft_putstr_fd(entry->value, v->out);
		ft_putstr_fd("\"", v->out);
	}
	ft_putstr_fd("\n", v->out);
}

void	export_builtin(char **cmd, t_var *v)
{
	t_list	*temp;
	t_entry	*entry;

	if (cmd[1] == NULL)
	{
		temp = v->env;
		while (temp)
		{
			entry = to_entry(temp->content);
			if (entry->is_exported == true)
				export_print(v, entry);
			temp = temp->next;
		}
	}
	else if (v->previous == NULL && v->head->next == NULL)
		try_export_value(cmd, v, true, 1);
}
