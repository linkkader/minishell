//
// Created by Abdoul Kader on 10/10/2022.
//

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/22 11:27:23 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_builtin(t_cmd *tmp)
{
	char	*name;

	name = tmp->args[0];
	if (ft_strcmp(name, "cd") == 0)
		cd_builtin(tmp);
	else if (ft_strcmp(name, "echo") == 0)
		echo_builtin(tmp);
	else if (ft_strcmp(name, "exit") == 0)
		exit_builtin(tmp);
	else if (ft_strcmp(name, "pwd") == 0)
		pwd_builtin(tmp);
	else if (ft_strcmp(name, "export") == 0)
		export_builtin(tmp);
	else if (ft_strcmp(name, "unset") == 0)
		unset_builtin(tmp);
	else
		tmp->path = get_cmd_pathk(tmp,
				tmp->args[0]);
}
