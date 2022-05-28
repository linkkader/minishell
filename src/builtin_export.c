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

static void	clear(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
}

static	void export_value(char *key, char *value,  t_var *var, t_bool is_in_export)
{
	t_list	*temp;
	t_entry *entry;
	t_bool	is_in;

	temp = var->env;
	entry = to_entry(temp);
	is_in = false;
	while (temp)
	{
		if (ft_strncmp(key, entry->key, ft_strlen(entry->key)) == 0)
		{
			entry->value =  value;
			is_in = true;
			break;
		}
		temp = temp->next;
	}
	if (is_in == false)
	{
		entry = malloc(sizeof(*entry));
		if (entry == NULL)
			return ;
		entry->key = key;
		entry->is_exported = is_in_export;
		entry->value = value;
		ft_lstadd_back(&var->env, ft_lstnew(entry));
	}
}

void try_export_value(char **sp, t_var *var,t_bool is_in_export, int start)
{
	int 	i;
	t_bool 	bool;
	int 	j;

	i = start;
	bool = true;
	while (sp && sp[i] && bool == true)
	{
		j = 0;
		while (sp[i][j])
		{
			if (sp[i][j] == '=')
			{
				bool = true;
				break;
			}
			j++;
		}
		if (j != ft_strlen(sp[i]))
		{
			export_value(ft_substr(sp[i], 0, j),
						 ft_substr(sp[i], j + 1, ft_strlen(sp[i]) - j -  1),
						 var, is_in_export
			);
		}
		else
		{
			ft_putstr_fd(ERR_CMD, var->console_fd);
			ft_putstr_fd(sp[0], var->console_fd);
			ft_putstr_fd("\n", var->console_fd);
			clear(sp);
			break;
		}
		i++;
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
			if (entry->is_exported == true && entry->value != NULL)
				printf("declare -x %s=\"%s\"\n", entry->key, entry->value);
			else if (entry->is_exported== true)
				printf("declare -x %s\n", entry->key);
			temp = temp->next;
		}
	}
	else
	{
		try_export_value(cmd, v, true, 1);
	}
}