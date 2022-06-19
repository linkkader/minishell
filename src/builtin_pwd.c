/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/05/25 15:45:03 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_builtin(char **cmd, t_var *v)
{
	char	*path;

	path = malloc(1000);
	if (path == NULL)
	{
		perror("pwd");
		return ;
	}
	if (cmd[1] == NULL)
	{
		getcwd(path, 0);
		ft_putstr_fd(path, v->out);
		ft_putstr_fd("\n", v->out);
	}
	else
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
	}
	free(path);
}
