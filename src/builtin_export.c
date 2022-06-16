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

static void	export_value(char *key, char *value, t_var *var,
			t_bool is_in_export)
{
	t_list	*temp;
	t_entry	*entry;
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
			break ;
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

void	part_part(char *str,t_util *util)
{
	char	*value;
	char	*t;
	char	*key;
	t_list	*temp;
	t_entry	*entry;

	temp = util->var->env;
	util->bool = true;
	t = NULL;
	key= ft_substr(str, 0, util->j);
	while (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, key, strlen(key) + 1) == 0)
			t = entry->value;
		temp = temp->next;
	}
	if (t != NULL)
		value = strjoin(t,
					ft_substr(str, util->j + 2, ft_strlen(str) - util->j - 1));
	else
		value = ft_substr(str, util->j + 2, ft_strlen(str) - util->j - 1);
	free(t);
	export_value(ft_substr(str, 0, util->j),
				 value,util->var, util->is_in_export);
}

void	part(char *str,t_util *util)
{
	if (!(ft_isalpha(str[util->j]) == 1 || str[util->j] == '_'))
	{
		util->bool = true;
		not_an_identifier(util->var);
	}
	while (util->bool == false && str[util->j])
	{
		if (util->bool == false && str[util->j] == '+' && str[util->j + 1] == '=')
			part_part(str,util);
		if (!(ft_isalpha(str[util->j]) == 1 || ft_isalnum(str[util->j]) == 1 ||
			  str[util->j] == '_'))
		{
			util->bool = true;
			if (str[util->j] == '=')
				export_value(ft_substr(str, 0, util->j),
							 ft_substr(str, util->j + 1, ft_strlen(str) - util->j - 1),
							 util->var, util->is_in_export);
			else
				not_an_identifier(util->var);
			break ;
		}
		util->j++;
	}
}

//[a-zA-Z_][a-zA-Z0-9_]
void	try_export_value(char **sp, t_var *var,
			t_bool is_in_export, int start)
{
	t_util	util;

	util.i = start;
	util.var = var;
	util.is_in_export = is_in_export;
	while (sp && sp[util.i])
	{
		util.j = 0;
		util.bool = false;
		part(sp[util.i], &util);
		(util.i)++;
		if (util.bool == true)
			continue ;
		if (util.is_in_export == true && util.j == ft_strlen(sp[util.i - 1]))
		{
			export_value(ft_substr(sp[util.i - 1], 0, util.j),
				NULL, var, util.is_in_export);
			continue ;
		}
		ft_putstr_fd(ERR_CMD, var->console_fd);
		ft_putstr_fd(sp[util.i - 1], var->console_fd);
		ft_putstr_fd("\n", var->console_fd);
		break ;
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
