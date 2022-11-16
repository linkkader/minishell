//
// Created by Abdoul kader Coulibaly on 11/16/22.
//

#include "../includes/header.h"


int	infile(t_file *tFile, int in, int *error)
{
	int 	fd;

	fd = open(tFile->name, O_RDONLY);
	if (fd < 0)
	{
		*error = 1;
		perror("minishell");
	}
	else
	{
		dup2(fd, in);
	}
	return (in);
}

int	outfile(t_file *tFile, int out, int *error)
{
	int 	fd;

	fd = open(tFile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("minishell");
	else
	{
		//todo: need check if correct
		dup2(fd, out);
	}
	return (out);
}

int append_file(t_file *tFile, int out,  int *error)
{
	int 	fd;

	fd = open(tFile->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror("minishell");
	else
	{
		//todo: need check if correct
		dup2(fd, out);
	}
	return (out);
}
