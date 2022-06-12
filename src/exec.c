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

static void	my_clear(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
}

static char	**check_builtin(t_command *head, t_var *var)
{
	char	*name;

	if (head == NULL)
		return (NULL);
	name = head->command_name;
	if (ft_strncmp(name, "exit", ft_strlen(name)) == 0)
		exit_builtin(head->command_args, var);
	else if (ft_strncmp(name, "unset", ft_strlen(name)) == 0)
		unset_builtin(head->command_args, var);
	else if (ft_strncmp(name, "export", ft_strlen(name)) == 0)
		export_builtin(head->command_args, var);
	else if (ft_strncmp(name, "cd", ft_strlen(name)) == 0)
		cd_builtin(head->command_args, var);
	else if (ft_strncmp(name, "pwd", ft_strlen(name)) == 0)
		pwd_builtin(head->command_args, var);
	else if (ft_strncmp(name, "env", ft_strlen(name)) == 0)
		env_builtin(head->command_args, var);
	else if (ft_strncmp(name, "echo", ft_strlen(name)) == 0)
		echo_builtin(head->command_args, var);
	else
		return (head->command_args);
	return (NULL);
}


char	**check_cmd(t_var *v, t_command *head, char **path)
{
	char	**sp;

	if (head == NULL)
		return (NULL);
	sp = head->command_args;
	printf("%s\n", head->command_name);
	if (sp == NULL)
		return (NULL);
	if (check_builtin(head, v) == NULL)
		return (NULL);
	if (head && sp != NULL)
	{
		path[0] = head->command_path;
		return (head->command_args);
	}
	try_export_value(sp, v, false, 0);
	return (NULL);
}

int	to_pipe(int fd)
{
	int		pdes[2];
	pid_t	child;
	char	c;

	pipe(pdes);
	child = fork();
	if (child == -1)
		perror("Pipe");
	else if (child == 0)
	{
		dup2(pdes[1], STDOUT_FILENO);
		while (read(fd, &c, 1) > 0)
			write(1, &c, 1);
		exit(1);
	}
	wait(NULL);
	close(pdes[1]);
	return (pdes[0]);
}