/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_all_strings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:35:58 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/01 18:53:49 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	replace_all_strings(char **strs, char new, char old)
{
	int	i;

	i = -1;
	while (strs[++i])
		replace_inside_quotes(strs[i], new, old);
}
