/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:10:28 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:23 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/header.h"

void	sigint_handler_nonl(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	sigint_handler_in_process(int sig)
{
	(void) sig;
	ft_putstr_fd("sigint \n", 2);
	printf("\n");
}

void	sigquit_handler_in_process(int sig)
{
	(void) sig;
	ft_putstr_fd("siquit \n", 2);
	printf("Quit: %d\n", sig);
}

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		(void) sig;
	}
}

void	signals(void)
{
	g_global.sig_int = signal(SIGINT, handler);
	g_global.sig_quit = signal(SIGQUIT, SIG_IGN);
}

void	reset_signals()
{
	signal(SIGINT, g_global.sig_int);
	signal(SIGQUIT, g_global.sig_quit);
}