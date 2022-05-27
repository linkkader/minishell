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

void	cd_builtin(char **cmd)
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

void	pwd_builtin(char **cmd)
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

void	exit_builtin(char **cmd)
{
	//free all value here
	exit(0);
}