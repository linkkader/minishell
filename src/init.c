//
// Created by Abdoul Kader on 12/11/2022.
//

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

static void print2d(char **arr)
{
	int i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

static char **copy(char **env)
{
	char **cpy;
	int i;

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

void	print_all_entries()
{
	t_entry *entry;

	t_list *lst = g_global.entries;
	while (lst)
	{
		entry = to_entry(lst->content);
		ft_putstr_fd(entry->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(entry->value, 1);
		ft_putstr_fd("\n", 1);
		lst = lst->next;
	}
}

void	env_to_entries(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		push_entry(&g_global.entries, env[i]);
		i++;
	}
}

void	update_env()
{
	t_entry *entry;
	int		i;
	t_list	*temp;
	char	*str;

	i = 0;
	clear_d2(g_global.env);
	g_global.env = malloc((ft_lstsize(g_global.entries) + 1) * sizeof(char *));
	if (g_global.env == NULL)
		return ;
	temp = g_global.entries;
	while (temp)
	{
		entry = to_entry(temp->content);
		str = ft_strjoin(entry->key, "=");
		if (g_global.env[i] == NULL)
			return ;
		g_global.env[i] = ft_strjoin(str, entry->value);
		if(str)
			free(str);
		if (g_global.env[i])
			return ;
		temp = temp->next;
	}
}

void	init(char **env)
{
	g_global.env = copy(env);
	if (g_global.env == NULL)
		return ;
	g_global.entries = NULL;
	env_to_entries(g_global.env);
	signals();
}