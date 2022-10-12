/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_get_env(t_var *var, char *name)
{
	t_entry		*entry;
	t_list		*temp;

	temp = var->env;
	while (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, name, ft_strlen(name) + 1) == 0)
			return (entry->value);
		temp = temp->next;
	}
	return (NULL);
}

void	env_builtin(char **cmd, t_var *v)
{
	t_list	*temp;
	t_entry	*entry;

	if (cmd[1] == NULL)
	{
		temp = v->env;
		while (temp)
		{
			entry = to_entry(temp->content);
			if (entry->is_exported == true && entry->value != NULL)
			{
				ft_putstr_fd(entry->key, v->out);
				ft_putstr_fd("=", v->out);
				ft_putstr_fd(entry->value, v->out);
				ft_putstr_fd("\n", v->out);
			}
			temp = temp->next;
		}
	}
	else
		ft_putstr_fd("env: too many arguments\n", 2);
}
