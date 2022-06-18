/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:07:05 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/16 13:59:31 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect(char *token)
{
	if (p_ft_strcmp("<", token))
		if (p_ft_strcmp(">", token))
			if (p_ft_strcmp(">>", token))
				if (p_ft_strcmp("<<", token))
					return (0);
	return (1);
}

char	*get_command_path(char *command_name, char **env)
{
	char	*path;
	char	*command_path;
	char	**paths;
	int		i;

	if (!access(command_name, F_OK))
		return (p_ft_strdup(command_name));
	i = -1;
	path = p_ft_getenv("PATH", env);
	if 	(!path)
		return (NULL);
	split(&paths, path, ':');
	free(path);
	path = strjoin("/", command_name);
	while (paths[++i])
	{
		command_path = strjoin(paths[i], path);
		if (!access(command_path, F_OK))
		{
			i = 0;
			while (paths[i])
				i++;
			clear(paths, i);
			free(path);
			return (command_path);
		}
		free(command_path);
		command_path = NULL;
	}
	clear(paths, i);
	free(path);
	puterror(command_name, "command not found");
	return (NULL);
}


void	get_cmds(t_command *cmds, char **env)
{
	int		i;

	while (cmds)
	{
		i = -1;
		while (cmds->tokens->tokens[++i])
		{
			if (!redirect(cmds->tokens->tokens[i]) && ((i && !redirect(cmds->tokens->tokens[i - 1])) || !i))
			{
				if (!cmds->command_name)
				{
					cmds->command_name = remove_quotes(expand_var(p_ft_strdup(cmds->tokens->tokens[i]), env, 0));
					cmds->command_path = get_command_path(p_ft_strdup(cmds->command_name), env);
				}
				cmds->command_args = p_ft_realloc(cmds->command_args, remove_quotes(expand_var(p_ft_strdup(cmds->tokens->tokens[i]), env, 0)));
			}
		}
		cmds = cmds->next;
	}
}
