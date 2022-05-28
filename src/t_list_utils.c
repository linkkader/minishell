/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert3_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:38:23 by acouliba          #+#    #+#             */
/*   Updated: 2022/04/11 17:38:25 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	push(t_list **lst, char *str)
{
	t_entry		*entry;
	char		sp;
	int 		i;

	entry = malloc(sizeof(*entry));
	if (entry == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break;
		i++;
	}
	if (i == ft_strlen(str))
	{
		entry->key = ft_strdup(str);
		entry->value = NULL;
	}
	else
	{
		entry->key = ft_substr(str, 0, i);
		entry->value = ft_substr(str, i + 1, ft_strlen(str) - i -1);
	}
	//entry->is_exported = malloc(sizeof(t_bool));
	//if (entry->is_exported == NULL)
	//	return ;
	entry->is_exported = true;
	ft_lstadd_back(lst, ft_lstnew(entry));
}

t_entry	*to_entry(void *e)
{
	return ((t_entry *)(e));
}