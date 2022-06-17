/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/17 20:09:36 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	correct_echo(t_var *v)
{
	struct termios	attributes;

	if (v->attributes == NULL)
	{
		v->attributes = malloc(sizeof(struct termios));
		if (v->attributes == NULL)
			return ;
		tcgetattr(STDIN_FILENO, v->attributes);
	}
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~~(ECHO | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

void	normal_echo(t_var *v)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, v->attributes);
}
