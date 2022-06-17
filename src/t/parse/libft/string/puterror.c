/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:17:57 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/07 18:32:58 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	puterror(char *name, char *error)
{
	write(2, name, p_ft_strlen(name));
	write(2, ": ", 2);
	write(2, error, p_ft_strlen(error));
	write(2, "\n", 1);
	return (1);
}