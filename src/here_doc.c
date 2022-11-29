/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:00:40 by acouliba          #+#    #+#             */
/*   Updated: 2022/11/29 17:00:43 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	sigint(int sig)
{
	(void) sig;
	g_global.std_in = dup(0);
	close(0);
}

static void	sigquit(int sig)
{
	(void) sig;
}

static char	*part(t_file *tFile, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, tFile->name) == 0)
		{
			g_global.doc_here_status = 0;
			free(line);
			break ;
		}
		line = ft_expand(line);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	return (line);
}

int	here_doc(t_file *tFile, int in, int *error)
{
	int		fd[2];
	char	*line;
	sig_t	sig;

	sig = signal(SIGINT, sigint);
	g_global.doc_here_status = 1;
	if (pipe(fd))
	{
		perror("minishell");
		exit(errno);
	}
	line = part(tFile, fd);
	dup2(g_global.std_in, 0);
	close(fd[1]);
	dup2(fd[0], in);
	signal(SIGINT, sig);
	return (in);
}
