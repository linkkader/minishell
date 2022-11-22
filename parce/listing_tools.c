/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:49:04 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/21 15:26:52 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	ft_lstadd_back(t_file **lst, t_file *new)
{
	t_file	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_file	*ft_lstlast(t_file *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (0);
}

t_file	*ft_lstnew(int token, char *name)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (name)
	{
		if (!new)
			return (NULL);
		new -> name = ft_strdup(name);
		new -> token = token;
		new -> next = NULL;
	}
	return (new);
}
