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

void	cd_builtin(char **cmd, t_var *v)
{
	char	*path;

	if (v->previous  != NULL || v->head->next != NULL)
		return ;
	chdir(path);
	if (cmd[1] == NULL)
		path = ft_get_env(v, "HOME");
	else
		path = cmd[1];
	if (access(path, X_OK) == 0)
		chdir(path);
	else
		perror("cd");
}
