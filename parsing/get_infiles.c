/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:49:58 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/06 18:33:29 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    get_infiles(t_command *cmds, char **env)
{
	char	*infile;
    int 	i;
    int		fd;

	fd = -1;
	while (cmds)
	{
		i = -1;
		while (cmds->tokens->tokens[++i])
		{
			if (i && !parse_ft_strcmp("<", cmds->tokens->tokens[i - 1]))
			{
				// if (cmds->input != -1)
				// 	close();
				infile = remove_quotes(expand_var(cmds->tokens->tokens[i], env, 0));
				fd = open(infile, O_RDONLY);
				if (fd == -1 || access(cmds->tokens->tokens[i], F_OK))
				{
					cmds->should_execute = 0;
					puterror(cmds->tokens->tokens[i], strerror(errno));
				}
				if (i > cmds->tokens->index)
					cmds->input = fd;
			}
		}
		cmds = cmds->next;
	}
}