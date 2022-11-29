/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:28:22 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/29 14:40:32 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

static void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	cmd = NULL;
}

void	free_list(t_cmd *data)
{
	t_file	*tmp;
	t_cmd	*tmp_data;

	free(g_global.line);
	g_global.line = NULL;
	while (data)
	{
		while (data->file)
		{
			tmp = data->file;
			data->file = data->file->next;
			free(tmp->name);
			free(tmp);
		}
		if (data->cmd)
			free_cmd(data->cmd);
		tmp_data = data;
		data = data->next;
		free(tmp_data);
		tmp_data = NULL;
	}
}
