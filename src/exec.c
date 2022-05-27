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

static void	clear(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
}

static char	**check_builtin(char **cmd, t_var *var)
{
	if (cmd == NULL)
		return (cmd);
	if (ft_strncmp(cmd[0], "/usr/bin/cd", ft_strlen(cmd[0])) == 0)
		cd_builtin(cmd, var);
	else if (ft_strncmp(cmd[0], "/bin/pwd", ft_strlen(cmd[0])) == 0)
		pwd_builtin(cmd, var);
	else if (ft_strncmp(cmd[0], "/usr/bin/env", ft_strlen(cmd[0])) == 0)
		env_builtin(cmd, var);
	else
		return (cmd);
	return (NULL);
}

static char	*ft_strjoin2(char *str1, char *str2, char *split)
{
	char	*str;
	int		length1;
	int		length2;
	int		i;

	i = -1;
	length1 = ft_strlen(str1);
	length2 = ft_strlen(str2);
	str = malloc((length1 + length2 + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (++i < length1)
		str[i] = str1[i];
	if (split != NULL)
		str[i] = *split;
	else
		i--;
	length1 = -1;
	while (++length1 < length2)
		str[++i] = str2[length1];
	str[++i] = '\0';
	return (str);
}

static char	*path(t_list *lst)
{
	while (lst)
	{
		if (ft_strncmp ("PATH=/", lst->content, 6) == 0)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

static void init(t_var *var)
{
	char	*str;

	str = path(var->env);
	var->sp = ft_split(str, ':');
}

char	**check_cmd(t_var v, int index, int console)
{
	char	**sp;
	int		i;
	char	*s;

	i = 0;
	init(&v);
	sp = ft_split(v.cmd[index], ' ');
	if (sp == NULL)
		return (NULL);
	if (access(sp[0], X_OK) == 0)
		return (sp);
	if (ft_strncmp(sp[0], "exit", ft_strlen(sp[0])) == 0)
		exit_builtin(sp, &v);
	while (v.sp[i])
	{
		s = ft_strjoin2(v.sp[i], sp[0], "/");
		if (access(s, X_OK) == 0)
		{
			free(sp[0]);
			sp[0] = s;
			return (check_builtin(sp, &v));
		}
		free(s);
		i++;
	}
	ft_putstr_fd(ERR_CMD, console);
	ft_putstr_fd(sp[0], console);
	ft_putstr_fd("\n", console);
	clear(sp);
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