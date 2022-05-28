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

static void	clear(char **cmd)
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
	clear(cmd);
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
	clear(cmd);
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
}

void	exit_builtin(char **cmd, t_var *v)
{
	//free all value here
	exit(0);
}