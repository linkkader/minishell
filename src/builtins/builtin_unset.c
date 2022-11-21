/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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

static void	delete_item(t_list **lst, char *str)
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

void	unset_builtin(t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->cmd[i])
	{
		delete_item(&g_global.entries, cmd->cmd[i]);
		i++;
	}
	clear_d2(g_global.env);
	//env_to_entries
	//env_to_entries();
	//g_global.env = to_env(g_global.entries, true);
}
