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

#include "pipex.h"

static void	clear(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
}

void	exec_doc(int *pdes, char *limit)
{
	char	*str;
	pid_t	child2;

	while (1)
	{
		write(1, "pipe heredoc> ", ft_strlen("pipe heredoc> "));
		close(pdes[0]);
		str = read_line(STDIN_FILENO);
		if (ft_strncmp(str, limit, ft_strlen(limit)) == 0)
			break ;
		child2 = fork();
		if (child2 == -1)
			perror("Pipe");
		else if (child2 == 0)
		{
			dup2(pdes[1], STDOUT_FILENO);
			close(pdes[0]);
			write(1, str, ft_strlen(str));
			exit(1);
		}
		free(str);
		wait(NULL);
	}
	free(str);
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

char	**check_cmd(t_var v, int index, t_command *head, char **path)
{
	if (head && head->command_args != NULL)
	{
		path[0] = head->command_path;
		return (head->command_args);
	}
	ft_putstr_fd(ERR_CMD, v.console_fd);
	ft_putstr_fd(head->command_name, v.console_fd);
	ft_putstr_fd("\n", v.console_fd);
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
