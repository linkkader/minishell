/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_part2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	*part(char **sp, char *name)
{
	char	*p;
	int		i;
	char	*str;

	i = 0;
	while (sp[i])
	{
		str = ft_strjoin(sp[i], "/");
		if (str == NULL)
			return (NULL);
		p = ft_strjoin(str, name);
		free(str);
		if (p == NULL)
			return (NULL);
		if (access(p, X_OK) == 0)
			return (p);
		free(p);
		i++;
	}
	return (NULL);
}

static char	*part2(char *path, t_cmd *cmd, char *name)
{
	char	**sp;
	char	*p;

	p = NULL;
	if (path != NULL)
	{
		sp = ft_split(path, ':');
		if (sp)
			p = part(sp, name);
		if (p == NULL)
		{
			cmd->error = 127;
			put_error(name, "command not found");
		}
		clear_d2(sp);
		free(sp);
	}
	else
	{
		cmd->error = 127;
		put_error(name, "No such file or directory");
	}
	free(path);
}

char	*get_cmd_path(t_cmd *cmd, char *name)
{
	char	*path;
	char	*p;
	DIR		*dir;

	if (access(name, X_OK) == 0)
	{
		dir = opendir(name);
		if (dir != NULL)
		{
			closedir(dir);
			if (name[0] == '/')
			{
				put_error(name, "is a directory");
				cmd->error = 126;
				g_global.exit_code = 126;
				return (NULL);
			}
		}
		else
			return (ft_strdup(name));
	}
	path = ft_get_env("PATH");
	p = part2(path, cmd, name);
	return (p);
}
