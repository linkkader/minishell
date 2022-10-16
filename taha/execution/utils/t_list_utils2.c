/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static char	*to_env_part(t_list *list, t_bool real)
{
	t_entry	*entry;
	char	*temp;
	char	*str;

	entry = to_entry(list->content);
	if (real == true && (entry->value == NULL))
		return (NULL);
	if (real == true && ft_strlen(entry->value) == 0)
		return (NULL);
	temp = ft_strjoin(entry->key, "=");
	if (temp == NULL)
		return (NULL);
	str = ft_strjoin(temp, entry->value);
	free(temp);
	return (str);
}

char	**to_env(t_list *list, t_bool real)
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
		temp = to_env_part(list, real);
		if (temp != NULL)
			env[i++] = temp;
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}

void entries_lst()
{
	int		i;

	i = 0;
	while (g_global.env[i])
	{
		push(&g_global.entries, g_global.env[i]);
		i++;
	}
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}