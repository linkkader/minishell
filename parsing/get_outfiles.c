/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:33:45 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/06 18:34:15 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    get_outfiles(t_command *cmds, char **env)
{
    int i;
    int	fd;

	fd = -1;
	while (cmds)
	{
		i = -1;
		while (cmds->tokens->tokens[++i])
		{
			if (i && (!parse_ft_strcmp(">", cmds->tokens->tokens[i - 1]) || !parse_ft_strcmp(">>", cmds->tokens->tokens[i - 1])))
			{
				if (cmds->output != 1)
					close(cmds->output);
                if (!parse_ft_strcmp(">", cmds->tokens->tokens[i - 1]))
				    fd = open(cmds->tokens->tokens[i], O_RDWR | O_CREAT, 0644);
                else
				    fd = open(cmds->tokens->tokens[i], O_RDWR | O_CREAT | O_APPEND, 0644);
				cmds->output = fd;
				if (fd == -1)
				{
					puterror(cmds->tokens->tokens[i], strerror(errno));
					cmds->should_execute = 0;
				}
			}
		}
		cmds = cmds->next;
	}
}