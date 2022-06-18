/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/17 20:09:36 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_clear(char ***cmd)
{
	int		i;

	i = 0;
	while (cmd[0] && cmd[0][i])
		free(cmd[0][i++]);
	if (cmd[0])
		free(cmd[0]);
}

char	*to_env_part(t_list *list)
{
	t_entry	*entry;
	char	*temp;
	char	*str;

	entry = to_entry(list->content);
	//if (entry->is_exported == false || entry->value == NULL)
	//	return (NULL);
	temp = ft_strjoin(entry->key, "=");
	if (temp == NULL)
		return (NULL);
	str = ft_strjoin(temp, entry->value);
	free(temp);
	return (str);
}

char	**to_env(t_list *list)
{
	char	**env;
	int		i;
	char	*temp;

	i = 0;
	env = malloc((ft_lstsize(list) + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	while (list)
	{
		temp = to_env_part(list);
		if (temp != NULL)
			env[i++] = temp;
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}
