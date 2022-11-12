/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	_part_part(char *str, t_util *util, char *t, t_entry *entry)
{
	char	*value;
	char	*key;

	if (t != NULL)
	{
		key = ft_substr(str, util->j + 2,
				ft_strlen(str) - util->j - 1);
		value = ft_strjoin(t, key);
		entry->value = value;
		free(t);
		free(key);
	}
	else
	{
		value = ft_substr(str, util->j + 2, ft_strlen(str) - util->j - 1);
		export_value(ft_substr(str, 0, util->j),
			value, util->var, util->is_in_export);
	}
}

static void	part_part(char *str, t_util *util)
{
	char	*key;
	t_list	*temp;
	t_entry	*entry;
	char	*t;

	temp = util->var->env;
	util->bool = true;
	t = NULL;
	key = ft_substr(str, 0, util->j);
	if (key == NULL)
		return ;
	while (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, key, strlen(key) + 1) == 0)
			t = entry->value;
		temp = temp->next;
	}
	free(key);
	_part_part(str, util, t, entry);
}

static void	part(char *str, t_util *util)
{
	if (!(ft_isalpha(str[util->j]) == 1 || str[util->j] == '_'))
	{
		util->bool = true;
		not_an_identifier(util->var);
	}
	while (util->bool == false && str[util->j])
	{
		if (util->bool == false && str[util->j] == '+'
			&& str[util->j + 1] == '=')
			part_part(str, util);
		if (!(ft_isalpha(str[util->j]) == 1 || ft_isalnum(str[util->j]) == 1
				||str[util->j] == '_') && util->bool == false)
		{
			if (util->is_in_export == true)
				util->bool = true;
			if (str[util->j] == '=')
				export_value(ft_substr(str, 0, util->j),
					ft_substr(str, util->j + 1, ft_strlen(str) - util->j - 1),
					util->var, util->is_in_export);
			else if (util->bool == true)
				not_an_identifier(util->var);
			break ;
		}
		util->j++;
	}
}

static void	_try_export_value(t_var *var, char **sp, t_util util)
{
	ft_putstr_fd(sp[util.i - 1], var->console_fd);
	ft_putstr_fd(ERR_CMD, var->console_fd);
}

//util.i = start;
//util.var = var;
//util.is_in_export = is_in_export;
//[a-zA-Z_][a-zA-Z0-9_]
void	try_export_value(char **sp, t_var *var,
				t_bool is_in_export, int start)
{
	t_util	util;

	init_util(&util, start, var, is_in_export);
	while (sp && sp[util.i] && ft_strlen(sp[util.i]))
	{
		util.j = 0;
		util.bool = false;
		part(sp[util.i], &util);
		(util.i)++;
		if (util.bool == true)
			continue ;
		if (util.is_in_export == true
			&& util.j == (int)ft_strlen(sp[util.i - 1]))
		{
			export_value(ft_substr(sp[util.i - 1], 0, util.j),
				NULL, var, util.is_in_export);
			continue ;
		}
		var->tr = ft_try_exec(var, sp[util.i - 1], util.i - 1);
		if (var->tr != NULL)
			return ;
		_try_export_value(var, sp, util);
		break ;
	}
}
