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

void	delete_item(t_list **lst, char *str)
{
	t_list	*temp;
	t_list	*temp2;
	t_entry	*entry;

	temp = lst[0];
	if (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, str, ft_strlen(str) + 1) == 0)
		{
			free(entry->value);
			free(entry->key);
			temp2 = temp->next;
			free(temp);
			temp = temp2;
		}
		lst[0] = temp;
	}
	while (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, str, ft_strlen(str) + 1) == 0)
		{
			free(entry->value);
			free(entry->key);
			temp2->next = temp->next;
			free(temp);
			temp = temp2;
		}
		temp2 = temp;
		temp = temp->next;
	}
}

void	unset_builtin(char **cmd, t_var *v)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		delete_item(&v->env, cmd[i]);
		i++;
	}
}