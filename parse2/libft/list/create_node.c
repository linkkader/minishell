/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:35:38 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/06 10:24:08 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*create_node(t_command **head, char *line)
{
	t_command	*node;

	node = (t_command *)malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->tokens = (t_token *)malloc(sizeof(t_token));
	if (!node->tokens)
	{
		free(node);
		return (NULL);
	}
	node->tokens->line = line;
	node->command_name = NULL;
	node->command_path = NULL;
	node->next_line = NULL;
	node->tokens->limiters = (char **)p_ft_calloc(1, sizeof(char *));
	node->command_args = (char **)p_ft_calloc(1, sizeof(char *));
	node->should_execute = 1;
	node->input = 0;
	node->output = 1;
	node->next = NULL;
	p_ft_lstadd_back(head, node);
	return (node);
}
