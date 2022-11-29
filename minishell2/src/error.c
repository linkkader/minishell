/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:22:36 by acouliba          #+#    #+#             */
/*   Updated: 2022/11/29 17:22:39 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	put_error(char *str, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (error == NULL)
	{
		perror(str);
	}
	else
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
	}
}
