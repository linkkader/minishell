/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:46:01 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/28 18:46:13 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	size_double(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		;
	return (i);
}
