//
// Created by Abdoul Kader on 13/11/2022.
//

#include "../includes/header.h"

void	put_error(char *str, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	my_perror(int result, char *str)
{
	if (result)
	{
		perror(str);
	}
}