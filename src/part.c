/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:53 by acouliba          #+#    #+#             */
/*   Updated: 2022/11/29 17:26:54 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	update_env(void)
{
	t_entry	*entry;
	int		i;
	t_list	*temp;
	char	*str;

	i = 0;
	str = NULL;
	clear_d2(g_global.env);
	free(g_global.env);
	g_global.env = malloc((ft_lstsize(g_global.entries) + 1) * sizeof(char *));
	if (g_global.env == NULL)
		return ;
	temp = g_global.entries;
	while (temp)
	{
		entry = to_entry(temp->content);
		str = ft_strjoin(entry->key, "=");
		if (str == NULL)
			return ;
		g_global.env[i++] = ft_strjoin(str, entry->value);
		if (str)
			free(str);
		temp = temp->next;
	}
	g_global.env[i] = NULL;
}
