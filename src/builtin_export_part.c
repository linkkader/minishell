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

static void	not_an_identifier(t_var *var)
{
	ft_putstr_fd("minishell: export: ", var->console_fd);
	ft_putstr_fd("out", var->console_fd);
	ft_putstr_fd(": not a valid identifier\n", var->console_fd);
}

static void	part_part(char *str, t_util *util)
{
	char	*value;
	char	*t;
	char	*key;
	t_list	*temp;
	t_entry	*entry;

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
//free(t);

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
		{
			part_part(str, util);
		}
		if (!(ft_isalpha(str[util->j]) == 1 || ft_isalnum(str[util->j]) == 1
				||str[util->j] == '_') && util->bool == false)
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

static char	*path(t_list *lst, char *name)
{
	t_entry		*entry;
	char		**sp;
	char 		*p;
	int 		i;
	char 		*str;

	i = 0;
	if (access(name, X_OK) == 0)
		return (name);
	while (lst)
	{
		entry = to_entry(lst->content);
		if (ft_strncmp ("PATH", entry->key,
						ft_strlen(entry->key)) == 0)
			break ;
		lst = lst->next;
	}
	if (lst)
	{
		sp = ft_split(entry->value, ':');
		while (sp[i])
		{
			str = strjoin(sp[i], "/");
			if (str == NULL)
				return (NULL);
			p = strjoin(str, name);
			free(str);
			if (p == NULL)
				return (NULL);
			if (access(p, X_OK) == 0)
				return (p);
			free(p);
			i++;
		}
	}
	my_clear(&sp);
	return (NULL);
}

t_try	*ft_try_exec(t_var *var, char *name, int start)
{
	t_try	*t;

	t = malloc(sizeof(t_try));
	if (t == NULL)
		return (NULL);
	t->start = start;
	t->path = path(var->env, name);
	if (t->path == NULL)
	{
		free(t);
		return (NULL);
	}

	return (t);
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
		var->tr = ft_try_exec(var, sp[util.i - 1], util.i - 1);
		if (var->tr != NULL)
			return ;
		ft_putstr_fd(sp[util.i - 1], var->console_fd);
		ft_putstr_fd(ERR_CMD, var->console_fd);
		break ;
	}
}
