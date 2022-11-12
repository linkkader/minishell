/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_part2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	*part(char **sp, char *name)
{
	char	*p;
	int		i;
	char	*str;

	i = 0;
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
	return (NULL);
}

static char	*path(t_list *lst, char *name)
{
	t_entry		*entry;
	char		**sp;
	char		*p;

	if (access(name, X_OK) == 0)
		return (name);
	p = NULL;
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
		if (sp)
			p = part(sp, name);
		my_clear(&sp);
	}
	return (p);
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

void	not_an_identifier(t_var *var)
{
	ft_putstr_fd("minishell: export: ", var->console_fd);
	ft_putstr_fd("out", var->console_fd);
	ft_putstr_fd(": not a valid identifier\n", var->console_fd);
}
