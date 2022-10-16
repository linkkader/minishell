/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	part(t_list	*temp, t_list	*temp2, char *str)
{
	t_entry	*entry;

	while (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, str, ft_strlen(str) + 1) == 0)
		{
			free(entry->value);
			free(entry->key);
			free(temp->content);
			temp2->next = temp->next;
			free(temp);
			temp = temp2;
		}
		temp2 = temp;
		temp = temp->next;
	}
}

void	delete_item(t_list **lst, char *str)
{
	t_list	*temp;
	t_list	*temp2;
	t_entry	*entry;

	temp = lst[0];
	temp2 = NULL;
	if (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, str, ft_strlen(str) + 1) == 0)
		{
			free(entry->value);
			free(entry->key);
			free(temp->content);
			temp2 = temp->next;
			free(temp);
			temp = temp2;
		}
		lst[0] = temp;
	}
	part(temp, temp2, str);
}

void	unset_builtin(char **cmd, t_var *v)
{
	int		i;

	if (v->previous != NULL || v->head->next != NULL)
		return ;
	i = 1;
	while (cmd[i])
	{
		delete_item(&v->env, cmd[i]);
		i++;
	}
}
