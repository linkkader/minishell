//
// Created by Abdoul Kader on 19/6/2022.
//

#include "minishell.h"

void	sig_here_doc(int sig)
{
	(void) sig;
	g_global = -1;
	exit(0);
}