/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:51:30 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/18 18:44:00 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_line(int fd)
{
	char	*line;
	char	*new_line;
	char	*rd;

	write(1, "> ", 2);
	line = p_ft_calloc(1, sizeof(char));
	rd = (char *)p_ft_calloc(2, sizeof(char));
	while (read(fd, rd, 1) > 0 && rd[0] != '\n')
	{
		new_line = strjoin(line, rd);
		free(line);
		line = new_line;
	}
	free(rd);
	return (line);
}
