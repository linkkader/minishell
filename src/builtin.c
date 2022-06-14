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

char *ft_getenv(t_var *var, char *name)
{
	t_entry		*entry;
	t_list		*temp;

	temp = var->env;
	while (temp)
	{
		entry = to_entry(temp->content);
		if (ft_strncmp(entry->key, name, ft_strlen(name) + 1) == 0)
			return (entry->value);
		temp = temp->next;
	}
	return (NULL);
}

void	cd_builtin(char **cmd, t_var *v)
{
	char	*path;

	chdir(path);

	if (cmd[1] == NULL)
	{
		path = ft_getenv( v, "HOME");
	}
	else
		path = cmd[1];
	if (access(path, X_OK) == 0)
		chdir(path);
	else
		perror("cd");
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
		ft_putstr_fd(path, v->out);
		ft_putstr_fd("\n", v->out);
		free(path);
	}
	else
		ft_putstr_fd("pwd: too many arguments\n",2);
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
			{
				ft_putstr_fd(entry->key, v->out);
				ft_putstr_fd("=", v->out);
				ft_putstr_fd(entry->value, v->out);
				ft_putstr_fd("\n", v->out);
			}
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
		{
			ft_putstr_fd(cmd[i], v->out);
		}
		else
		{
			ft_putstr_fd(cmd[i], v->out);
			ft_putstr_fd(" ", v->out);
		}
		i++;
	}
	if (arg == false)
		ft_putstr_fd("\n", v->out);
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
}