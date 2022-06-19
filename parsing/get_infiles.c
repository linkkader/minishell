/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:49:58 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/18 18:33:25 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_infile(t_command *cmd, char *infile, int i)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1 || access(cmd->tokens->tokens[i], F_OK))
	{
		cmd->should_execute = 0;
		puterror(cmd->tokens->tokens[i], strerror(errno));
	}
	if (i > cmd->tokens->index && fd != -1)
	{
		if (cmd->input != 0)
			close(cmd->input);
		cmd->input = fd;
	}
	else if (fd != -1)
		close(fd);
	free(infile);
}

void	get_infiles(t_command *cmds, char **env)
{
	char	*infile;
	int		i;
	int		fd;

	fd = -1;
	while (cmds)
	{
		i = -1;
		while (cmds->tokens->tokens[++i] && cmds->should_execute)
		{
			if (i && !p_ft_strcmp("<", cmds->tokens->tokens[i - 1]))
			{
				infile = remove_quotes(\
				expand_var(p_ft_strdup(cmds->tokens->tokens[i]), env, 0));
				if (!p_ft_strlen(infile))
				{
					puterror(cmds->tokens->tokens[i], "ambiguous redirect");
					cmds->should_execute = 0;
				}
				else
					open_infile(cmds, infile, i);
			}
		}
		cmds = cmds->next;
	}
}
