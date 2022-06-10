/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/05/25 15:45:03 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	my_clear(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
}

void	cd_builtin(char **cmd, t_var *v)
{
	char	*path;

	if (cmd[1] == NULL)
		path = "~";
	else
		path = cmd[1];
	if (access(path, X_OK) == 0)
		chdir(path);
	else
		perror("cd");
	my_clear(cmd);
}

void	pwd_builtin(char **cmd, t_var *v)
{
	char 	*path;

	path = malloc(1000);
	if (path == NULL)
	{
		perror("pwd");
		return ;
	}
	if (cmd[1] == NULL)
	{
		getcwd(path, 1000);
		printf("%s\n", path);
		free(path);
	}
	else
	{
		ft_putstr_fd("pwd: too many arguments\n",2);
	}
	my_clear(cmd);
}

void	env_builtin(char **cmd, t_var *v)
{
	t_list	*temp;
	t_entry *entry;

	if (cmd[1] == NULL)
	{
		temp = v->env;
		while (temp)
		{
			entry = to_entry(temp->content);
			if (entry->is_exported == true && entry->value != NULL)
				printf("%s=%s\n", entry->key, entry->value);
			temp = temp->next;
		}
	}
	else
		ft_putstr_fd("env: too many arguments\n",2);
	my_clear(cmd);
}

void	exit_builtin(char **cmd, t_var *v)
{
	//free all value here
	exit(0);
}

void	echo_builtin(char **cmd, t_var *v)
{
	int 	i;
	t_bool 	arg;

	i = 1;
	arg = false;
	if (cmd[i] && ft_strncmp("-n", cmd[i], 2) == 0)
	{
		arg = true;
		i++;
	}
	while (cmd[i])
	{
		if (cmd[i + 1] == 0)
			printf("%s",cmd[i]);
		else
			printf("%s ",cmd[i]);
		i++;
	}
	if (arg == false)
		printf("\n");
	my_clear(cmd);
}

void	delete_item(t_list **lst, char *str)
{
	t_list	*temp;
	t_list	*temp2;
	t_entry *entry;

	temp = lst[0];
	if (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, str, ft_strlen(str) + 1) == 0)
		{
			printf("%s\n", entry->key);
			free(entry->value);
			free(entry->key);
			temp2 = temp->next;
			free(temp);
			temp = temp2;
		}
		lst[0] = temp;
	}
	while (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, str, ft_strlen(str) + 1) == 0)
		{
			printf("%s\n", entry->key);
			free(entry->value);
			free(entry->key);
			free(temp);
			temp2->next = temp->next;
			temp = temp2;
		}
		temp2 = temp;
		temp = temp->next;
	}
}

void	unset_builtin(char **cmd, t_var *v)
{
	int 	i;

	i = 1;
	while (cmd[i])
	{
		delete_item(&v->env, cmd[i]);
		i++;
	}
	my_clear(cmd);
}