/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:38:23 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	part(t_list **lst, char *str, int i, t_entry *entry)
{
	if (i == (int)ft_strlen(str))
	{
		entry->key = ft_strdup(str);
		if (entry->key == NULL)
			return ;
		entry->value = NULL;
	}
	else
	{
		entry->key = ft_substr(str, 0, i);
		entry->value = ft_substr(str, i + 1, ft_strlen(str) - i -1);
		if (entry->key == NULL || entry->value == NULL)
			return ;
	}
	entry->is_exported = true;
	ft_lstadd_back(lst, ft_lstnew(entry));
}

void	push(t_list **lst, char *str)
{
	t_entry	*entry;
	int		i;

	entry = malloc(sizeof(*entry));
	if (entry == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	part(lst, str, i, entry);
}

t_entry	*to_entry(void *e)
{
	return ((t_entry *)(e));
}

void	free_entry(void *content)
{
	t_entry	*entry;

	entry = to_entry(content);
	if (entry->value != NULL)
		free(entry->value);
	if (entry->key != NULL)
		free(entry->key);
	free(content);
}

int	size_t_command(t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
