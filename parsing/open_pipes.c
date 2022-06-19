/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:33:47 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/18 18:37:19 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipes(t_command *cmds, int ***pipes)
{
	int	i;
	int	size;

	i = 0;
	size = p_ft_lstsize(cmds);
	if (size < 2)
		return ;
	*pipes = (int **)malloc((size - 1) * sizeof(int *));
	if (!*pipes)
		return ;
	while (cmds)
	{
		if (!cmds->next)
			return ;
		(*pipes)[i] = (int *)malloc(2 * sizeof(int));
		if (pipe((*pipes)[i]) < 0)
			return ;
		cmds->output = (*pipes)[i][1];
		cmds->next->input = (*pipes)[i][0];
		i++;
		cmds = cmds->next;
	}
}
