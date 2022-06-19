//
// Created by Abdoul Kader on 19/6/2022.
//

#include "minishell.h"

extern int		g_global;

void	sig_here_doc(int sig)
{
	printf("\nminishell$ ");
	rl_replace_line("", 0);
	rl_redisplay();
	g_global = 1;
	(void) sig;
}