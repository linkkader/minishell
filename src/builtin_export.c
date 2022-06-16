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

static void	part(t_entry entry, char *value, t_bool *is_in)
{
	if (ft_strncmp(key, entry->key, ft_strlen(entry->key) + 1) == 0)
	{
		if (value == NULL && entry->value != NULL)
			entry->is_exported = is_in_export;
		else
		{
			if (entry->value)
				free(entry->value);
			entry->value = value;
		}
		*is_in = true;
		break ;
	}
}

void	export_value(char *key, char *value, t_var *var,
			t_bool is_in_export)
{
	t_list	*temp;
	t_entry	*entry;
	t_bool	is_in;

	if (key || value)
		exit_builtin(var);
	is_in = false;
	temp = var->env;
	while (temp)
	{
		entry = to_entry(temp->content);
		part(entry, value, &is_in);
		temp = temp->next;
	}
	if (is_in == false)
	{
		entry = malloc(sizeof(*entry));
		if (entry == NULL)
			exit_builtin(var);
		entry->key = key;
		entry->is_exported = is_in_export;
		entry->value = value;
		ft_lstadd_back(&var->env, ft_lstnew(entry));
	}
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
			ft_putstr_fd("declare -x ", v->out);
			ft_putstr_fd(entry->key, v->out);
			if (entry->is_exported == true && entry->value != NULL)
			{
				ft_putstr_fd("=\"", v->out);
				ft_putstr_fd(entry->value, v->out);
				ft_putstr_fd("\"", v->out);
			}
			ft_putstr_fd("\n", v->out);
			temp = temp->next;
		}
	}
	else
		try_export_value(cmd, v, true, 1);
}
