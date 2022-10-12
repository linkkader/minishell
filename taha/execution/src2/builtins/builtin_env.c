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

char	*ft_get_env(t_cmd *cmd, char *name)
{
	int 	i;
	int 	j;

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
			return (g_global.env[i] + j + 1);
		i++;
	}
	return (NULL);
//	t_entry		*entry;
//	t_list		*temp;
//
//	temp = var->env;
//	while (temp)
//	{
//		entry = to_entry(temp->content);
//		if (ft_strncmp(entry->key, name, ft_strlen(name) + 1) == 0)
//			return (entry->value);
//		temp = temp->next;
//	}
//	return (NULL);
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
//	t_list	*temp;
//	t_entry	*entry;
//
//	if (cmd[1] == NULL)
//	{
//		temp = v->env;
//		while (temp)
//		{
//			entry = to_entry(temp->content);
//			if (entry->is_exported == true && entry->value != NULL)
//			{
//				ft_putstr_fd(entry->key, v->out);
//				ft_putstr_fd("=", v->out);
//				ft_putstr_fd(entry->value, v->out);
//				ft_putstr_fd("\n", v->out);
//			}
//			temp = temp->next;
//		}
//	}
//	else
//		ft_putstr_fd("env: too many arguments\n", 2);
}
