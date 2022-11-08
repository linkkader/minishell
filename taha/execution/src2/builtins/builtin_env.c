/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*ft_get_env(char *name)
{
	int		i;
	int		j;

	i = 0;
	while (g_global.env[i])
	{
		j = 0;
		while (name[j] && g_global.env[i][j])
		{
			if (name[j] != g_global.env[i][j])
				break ;
			j++;
		}
		if (name[j] == '\0' && g_global.env[i][j] == '=')
			return ft_strdup((g_global.env[i] + j + 1));
		i++;
	}
	return (NULL);
}

void	env_builtin(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->args[1] == NULL)
		return ;
	while (g_global.env[i])
	{
		if (ft_strchr(g_global.env[i], '='))
		{
			ft_putstr_fd(g_global.env[i], cmd->out);
			ft_putstr_fd("\n", cmd->out);
		}
		i++;
	}
}
