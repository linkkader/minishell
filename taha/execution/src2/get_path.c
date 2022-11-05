/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_part2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_clear(char ***sp)
{
	int		i;

	i = 0;
	while (sp[0] && sp[0][i])
		free(sp[0][i++]);
	if (sp[0])
		free(sp[0]);
}

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

char	*get_cmd_pathk(t_cmd *cmd, char *name)
{
	char	*path;
	char	**sp;
	char	*p;

	if (access(name, X_OK) == 0)
		return (name);
	p = NULL;
	path = ft_get_env(cmd, "PATH");
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
		my_clear(&sp);
	}
	else
	{
		cmd->error = 127;
		put_error( name, "No such file or directory");
	}
	return (p);
}

//void	not_an_identifier(t_var *var)
//{
//	ft_putstr_fd("minishell: export: ", var->console_fd);
//	ft_putstr_fd("out", var->console_fd);
//	ft_putstr_fd(": not a valid identifier\n", var->console_fd);
//}