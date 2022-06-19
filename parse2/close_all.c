/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:54:14 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/06 16:14:02 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    close_all(t_command *cmds, int ***pipes)
{
    int i;
    int size;

    i = 0;
    size = p_ft_lstsize(cmds);
    while (++i < size)
        free((*pipes)[i - 1]);
    //free(*pipes);
}