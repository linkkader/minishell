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

static	void export_value(char *key, char *value,  t_var *var, t_bool is_in_export)
{
	t_list	*temp;
	t_entry *entry;
	t_bool	is_in;

	if (key || value)
	{
		//exit here
	}
	is_in = false;
	temp = var->env;
	while (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(key, entry->key, ft_strlen(entry->key) + 1) == 0)
		{
			if (value == NULL && entry->value != NULL)
			{
				entry->is_exported = is_in_export;
			}
			else
			{
				if (entry->value)
					free(entry->value);
				entry->value = value;
			}
			is_in = true;
			break;
		}
		temp = temp->next;
	}
	if (is_in == false)
	{
		entry = malloc(sizeof(*entry));
		if (entry == NULL)
		{
			//exit here
			return ;
		}
		entry->key = key;
		entry->is_exported = is_in_export;
		entry->value = value;
		ft_lstadd_back(&var->env, ft_lstnew(entry));
	}
}

static void	not_an_identifier(t_var *var)
{
	ft_putstr_fd("minishell: export: ", var->console_fd);
	ft_putstr_fd("out", var->console_fd);
	ft_putstr_fd(": not a valid identifier\n", var->console_fd);
}
//[a-zA-Z_][a-zA-Z0-9_]
void try_export_value(char **sp, t_var *var,t_bool is_in_export, int start)
{
	int 	i;
	t_bool 	bool;
	int 	j;

	i = start;
	while (sp && sp[i])
	{
		j = 0;
		bool = false;
		if (!(ft_isalpha(sp[i][j]) == 1 || sp[i][j] == '_'))
		{
			bool = true;
			not_an_identifier(var);
		}
		while (sp[i][j])
		{
			if (!(ft_isalpha(sp[i][j]) == 1 || ft_isalnum(sp[i][j]) == 1 || sp[i][j] == '_'))
			{
				bool = true;
				if (sp[i][j] == '=')
				{
					export_value(ft_substr(sp[i], 0, j),
								 ft_substr(sp[i], j + 1, ft_strlen(sp[i]) - j -  1),
								 var, is_in_export
					);
				}
				else
					not_an_identifier(var);
				break;
			}
			j++;
		}
		i++;
		if (bool == true)
			continue;
		if (is_in_export == true && j == ft_strlen(sp[i - 1]))
		{
			export_value(ft_substr(sp[i - 1], 0, j),
						 NULL,
						 var, is_in_export
			);
			continue;
		}
		ft_putstr_fd(ERR_CMD, var->console_fd);
		ft_putstr_fd(sp[i - 1], var->console_fd);
		ft_putstr_fd("\n", var->console_fd);
		break;
	}
}

void	export_builtin(char **cmd, t_var *v)
{
	t_list	*temp;
	t_entry *entry;

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
	{
		try_export_value(cmd, v, true, 1);
	}
	//ft_putstr_fd("the end", 2);
}