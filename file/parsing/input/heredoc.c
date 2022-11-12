/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:47:57 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/22 10:51:27 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handler(int sig)
{
	(void)sig;
}

void	reading(int fd, char *limit, char shld_exp, char shld_wr)
{
	char	*line;

	signal(SIGINT, sig_here_doc);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!p_ft_strcmp(limit, line))
		{
			free(line);
			break ;
		}
		if (shld_exp)
			line = expand_var(line, shld_exp);
		if (shld_wr)
		{
			write(fd, line, p_ft_strlen(line));
			write(fd, "\n", 1);
		}
		free(line);
	}
	if (shld_wr)
		close(fd);
	exit(0);
}

void	read_heredoc(t_command *cmds, char *limit, char shld_exp, char shld_wr)
{
	int		pipes[2];
	pid_t	pid;
	sig_t	sig;

	sig = signal(SIGINT, handler);
	if (shld_wr)
	{
		if (pipe(pipes) < 0)
			exit (puterror("", strerror(errno)));
		cmds->input = pipes[0];
	}
	pid = fork();
	if (!pid)
		reading(pipes[1], limit, shld_exp, shld_wr);
	if (shld_wr)
		close(pipes[1]);
	wait(&g_global.heredoc_exit);
	g_global.heredoc_exit = WEXITSTATUS(g_global.heredoc_exit);
	signal(SIGINT, sig);
}

void	get_heredocs(t_command *cmds)
{
	int	i;

	cmds->tokens->index = -1;
	while (cmds)
	{
		i = -1;
		while (cmds->tokens->tokens[++i])
		{
			if (!p_ft_strcmp("<<", cmds->tokens->tokens[i]))
			{
				cmds->tokens->should_expand = \
				!is_there_any_quote(cmds->tokens->tokens[i + 1]);
				cmds->tokens->limiters = p_ft_realloc(cmds->tokens->limiters, \
				remove_quotes(p_ft_strdup(cmds->tokens->tokens[i + 1])));
				cmds->tokens->index = i + 1;
			}
		}
		cmds = cmds->next;
	}
}

void	heredoc(t_command *cmds)
{
	int	i;

	get_heredocs(cmds);
	while (cmds)
	{
		i = -1;
		while (cmds->tokens->limiters[++i] && g_global.heredoc_exit != 99)
		{
			if (cmds->tokens->limiters[i + 1])
				read_heredoc(cmds, cmds->tokens->limiters[i], \
				cmds->tokens->should_expand, 0);
			else
				read_heredoc(cmds, cmds->tokens->limiters[i], \
				cmds->tokens->should_expand, 1);
		}
		cmds = cmds->next;
	}
}
