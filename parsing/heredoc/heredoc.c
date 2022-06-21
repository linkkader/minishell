/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:47:57 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/18 18:37:42 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_there_any_quote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
	return (0);
}

void	free_lines(char *line, char *new_line)
{
	free(line);
	free(new_line);
}

static void	handler(int sig)
{
	(void)sig;
}

void	herdoc_read(t_command *cmds, char *limit, char shld_exp, char shld_wr)
{
	char	*line;
	char	*new_line;
	int		pipes[2];
	pid_t 	pid;
	sig_t	sig;

	if (shld_wr)
	{
		if (pipe(pipes) < 0)
			exit (puterror("", strerror(errno)));
		cmds->input = pipes[0];
	}
	sig = signal(SIGINT, handler);
	pid = fork();
	if (pid == 0)
	{
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
			new_line = strjoin(line, "\n");
			if (new_line == NULL)
				break ;
			if (shld_wr)
				write(pipes[1], new_line, p_ft_strlen(new_line));
			free(line);
			free(new_line);
		}
		exit(0);
	}
	wait(&g_global);
	if (shld_wr)
		close(pipes[1]);
	g_global = WEXITSTATUS(g_global);
	signal(SIGINT, sig);
	//while (1);
	//while (1)
	//{
	//	line = readline("> ");
	//	if (g_global == 1)
	//	{
	//		cmds->next_line = p_ft_strdup(line);
	//		//free all here
	//		break ;
	//	}
	//	if (line == NULL)
	//		break;
	//	new_line = strjoin(line, "\n");
	//	if (shld_exp)
	//		new_line = expand_var(new_line, cmds->env, 1);
	//	if (shld_wr)
	//		write(pipes[1], new_line, p_ft_strlen(new_line));
	//	free_lines(line, new_line);
	//}
	//signal(SIGINT, sig);
	//g_global = 0;
	//free_lines(line, new_line);
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
	int			i;

	get_heredocs(cmds);
	while (cmds)
	{
		i = -1;
		while (cmds->tokens->limiters[++i] && g_global != 99)
		{
			if (cmds->tokens->limiters[i + 1])
				herdoc_read(cmds, cmds->tokens->limiters[i], \
				cmds->tokens->should_expand, 0);
			else
				herdoc_read(cmds, cmds->tokens->limiters[i], \
				cmds->tokens->should_expand, 1);
		}
		cmds = cmds->next;
	}
}
