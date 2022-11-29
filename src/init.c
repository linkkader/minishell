/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:43:52 by acouliba          #+#    #+#             */
/*   Updated: 2022/11/29 16:43:55 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	clear_d2(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
}

static void	print2d(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

static char	**copy(char **env)
{
	char	**cpy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	cpy = malloc((i + 1) * sizeof(char *));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		cpy[i] = ft_strdup(env[i]);
		if (cpy[i] == NULL)
		{
			clear_d2(cpy);
			free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void	env_to_entries(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
			push_entry(&g_global.entries, env[i]);
		i++;
	}
}

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

void	init(char **env)
{
	g_global.env = copy(env);
	g_global.std_in = 0;
	g_global.doc_here_status = 0;
	g_global.entries = NULL;
	if (g_global.env == NULL)
		return ;
	env_to_entries(g_global.env);
	signals();
}
