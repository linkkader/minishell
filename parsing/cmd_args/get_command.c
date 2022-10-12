/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:07:05 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/22 13:48:01 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect(char *token)
{
	if (p_ft_strcmp("<", token))
		if (p_ft_strcmp(">", token))
			if (p_ft_strcmp(">>", token))
				if (p_ft_strcmp("<<", token))
					return (0);
	return (1);
}

char	*search_in_path(char *cmd_name, char *path, char **paths)
{
	char	*cmd_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		cmd_path = strjoin(paths[i], path);
		if (!access(cmd_path, X_OK))
		{
			i = 0;
			while (paths[i])
				i++;
			clear(paths, i);
			free(path);
			return (cmd_path);
		}
		free(cmd_path);
		cmd_path = NULL;
	}
	clear(paths, i);
	free(path);
	free(cmd_name);
	return (NULL);
}

char	*get_cmd_path(char *cmd_name)
{
	char	*path;
	char	**paths;
	int		i;

	if (!access(cmd_name, X_OK))
		return (p_ft_strdup(cmd_name));
	else if (!p_ft_strlen(cmd_name))
		return (NULL);
	i = -1;
	path = p_ft_getenv("PATH");
	if (!path)
		return (NULL);
	split(&paths, path, ':');
	free(path);
	path = strjoin("/", cmd_name);
	return (search_in_path(cmd_name, path, paths));
}

void	get_cmds(t_command *cmds)
{
	int	i;

	while (cmds)
	{
		i = -1;
		while (cmds->tokens->tokens[++i])
		{
			if (!redirect(cmds->tokens->tokens[i]) && \
			((i && !redirect(cmds->tokens->tokens[i - 1])) || !i))
			{
				if (!cmds->cmd)
				{
					cmds->cmd = remove_quotes(expand_var(\
					p_ft_strdup(cmds->tokens->tokens[i]), 0));
					cmds->path = get_cmd_path(cmds->cmd);
					if (!cmds->path)
						cmds->cmd = p_ft_strdup(cmds->tokens->tokens[i]);
				}
				cmds->args = p_ft_realloc(cmds->args, remove_quotes(\
				expand_var(p_ft_strdup(cmds->tokens->tokens[i]), 0)));
			}
		}
		cmds = cmds->next;
	}
}
