/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	correct_echo(void)
{
	struct termios	attributes;

	if (g_global.attributes == NULL)
	{
		g_global.attributes = malloc(sizeof(struct termios));
		if (g_global.attributes == NULL)
			return ;
		tcgetattr(STDIN_FILENO, g_global.attributes);
	}
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= (ECHO | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

void	normal_echo(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, g_global.attributes);
}
