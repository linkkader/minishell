//
// Created by Abdoul Kader on 13/11/2022.
//

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
