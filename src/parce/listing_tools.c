/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:49:04 by ofarissi          #+#    #+#             */
/*   Updated: 2022/12/01 12:19:49 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	ft_lstadd_back_parse(t_file **lst, t_file *new)
{
	t_file	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = ft_lstlast_parse(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_file	*ft_lstlast_parse(t_file *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (0);
}

t_file	*ft_lstnew_parse(int token, char *name)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	if (name)
	{
		new -> name = ft_strdup_parse(name);
		new -> token = token;
		new -> next = NULL;
	}
	return (new);
}

t_cmd	*is_error(t_cmd *to_free, int i)
{
	g_global.exit_code = 258;
	free_list(to_free);
	check_last(i);
	return (NULL);
}
