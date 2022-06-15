/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:39:02 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/14 22:08:34 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_command *cmds, int ***pipes, char **env)
{
	heredoc(cmds);
	open_pipes(cmds, pipes);
	get_infiles(cmds, env);
	get_outfiles(cmds, env);
	get_cmds(cmds, env);
}
