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

static void	reset_setting(t_var *var)
{
	signal(SIGINT, sigint_handler_in_process);
	signal(SIGQUIT, sigquit_handler_in_process);
	tcgetattr(STDIN_FILENO, var->attributes);
	free(var->attributes);
}

void	exit_builtin(t_var *v)
{
	if (v->previous != NULL || v->head->next != NULL)
		return ;
	reset_setting(v);
	exit(0);
}
