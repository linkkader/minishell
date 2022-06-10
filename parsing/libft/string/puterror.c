/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:17:57 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/06 19:15:18 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	puterror(char *name, char *error)
{
	write(2, name, parse_ft_strlen(name));
	write(2, ": ", 2);
	write(2, error, parse_ft_strlen(error));
	write(2, "\n", 1);
	return (1);
}