/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:33:45 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/15 13:16:45 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_outfile(t_command *cmd, char *outfile, int i)
{
	int	fd;

	if (!p_ft_strcmp(">", cmd->tokens->tokens[i - 1]))
		fd = open(outfile, O_RDWR | O_CREAT, 0644);
	else
		fd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
	{
		if (cmd->output != 1)
			close(cmd->output);
		cmd->output = fd;
	}
	else
	{
		puterror(cmd->tokens->tokens[i], strerror(errno));
		cmd->should_execute = 0;
	}
}

void	get_outfiles(t_command *cmds, char **env)
{
	int		i;
	char	*outfile;

	while (cmds)
	{
		i = -1;
		while (cmds->tokens->tokens[++i] && cmds->should_execute)
		{
			if (i && (!p_ft_strcmp(">", cmds->tokens->tokens[i - 1]) \
			|| !p_ft_strcmp(">>", cmds->tokens->tokens[i - 1])))
			{
				outfile = remove_quotes(expand_var(\
				p_ft_strdup(cmds->tokens->tokens[i]), env, 0));
				if (!p_ft_strlen(outfile))
				{
					puterror(cmds->tokens->tokens[i], "ambiguous redirect");
					cmds->should_execute = 0;
				}
				else
					open_outfile(cmds, outfile, i);
			}
		}
		cmds = cmds->next;
	}
}
