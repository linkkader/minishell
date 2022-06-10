/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:19 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/06 11:52:13 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*tokenizer(char *str)
{
	int			i;
	t_command	*cmds;
	t_command	*node;
	char		**lines;

	i = -1;
	cmds = NULL;
	split(&lines, str, '|');
	if (!lines)
		return (NULL);
	while (lines[++i])
	{
		node = create_node(&cmds, lines[i]);
		if (!node)
		{
			parse_ft_lstclear(&cmds);
			return (NULL);
		}
		node->tokens->line = wrap_redirection_by_space(node->tokens->line);
		split(&node->tokens->tokens, node->tokens->line, ' ');
	}
	while (lines[i])
		free(lines[i++]);
	free(lines);
	return (cmds);
}
