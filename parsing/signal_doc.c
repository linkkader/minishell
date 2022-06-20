//
// Created by Abdoul Kader on 19/6/2022.
//

#include "minishell.h"

extern int		g_global;

void	sig_here_doc(int sig)
{
	printf("signal\n");
	(void) sig;
	g_global = -1;
	exit(0);
}