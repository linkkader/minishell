/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:33:00 by acouliba          #+#    #+#             */
/*   Updated: 2022/11/29 16:33:03 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	infile(t_file *tFile, int in, int *error)
{
	int		fd;

	fd = open(tFile->name, O_RDONLY);
	if (fd < 0)
	{
		*error = 1;
		put_error(tFile->name, NULL);
	}
	else
	{
		dup2(fd, in);
	}
	return (in);
}

int	outfile(t_file *tFile, int out, int *error)
{
	int		fd;

	fd = open(tFile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		*error = 1;
		put_error(tFile->name, NULL);
	}
	else
	{
		dup2(fd, out);
	}
	return (out);
}

int	append_file(t_file *tFile, int out, int *error)
{
	int		fd;

	fd = open(tFile->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		*error = 1;
		put_error(tFile->name, NULL);
	}
	else
	{
		dup2(fd, out);
	}
	return (out);
}
