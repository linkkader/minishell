/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:39:02 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/22 10:52:17 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_command *cmds, int ***pipes, char **env)
{
	g_global.env = env;
	heredoc(cmds);
	open_pipes(cmds, pipes);
	get_infiles(cmds);
	get_outfiles(cmds);
	get_cmds(cmds);
}
