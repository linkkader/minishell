/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:45:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/22 09:43:02 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//void	reset_setting(t_var *var)
//{
//	signal(SIGINT, var->sig_int);
//	signal(SIGQUIT, var->sig_quit);
//	tcgetattr(STDIN_FILENO, var->attributes);
//	free(var->attributes);
//}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	part(t_cmd *cmd)
{
	ft_putstr_fd("minishell: exit: ", 1);
	ft_putstr_fd(cmd->args[1], 1);
	ft_putstr_fd(" numeric argument required\n", 1);
	//reset_setting(v);
	exit(-1);
}

static int	len_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	exit_builtin(t_cmd *cmd)
{
	char	len;

//	if (v->previous != NULL || v->head->next != NULL)
//		return ;
	len = len_args(cmd->args);
	ft_putstr_fd("exit\n", 1);
	if (cmd->args[1] == NULL)
		exit(0);
	if (is_numeric(cmd->args[1]))
	{
		if (len > 2)
			ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		else
		{
			//reset_setting(v);
			exit(ft_atoi(cmd->args[1]));
		}
	}
	else
		part(cmd);
}
