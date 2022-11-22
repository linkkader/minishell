//
// Created by Abdoul Kader on 12/11/2022.
//

#include "../includes/header.h"

void	reset()
{
	normal_echo();
}

static	int init_prompt(void)
{
	correct_echo();
	signals();
	g_global.line = readline(PROMPT_CMD);
	if (!g_global.line)
	{
		ft_putstr_fd("exit\n", 1);
		reset();
		exit(g_global.exit_code);
	}
	g_global.doc_here_status = 0;
	if (!ft_strlen(g_global.line))
		return (1);
	add_history(g_global.line);
	return (0);
}

int main(int ac, char **av, char **env)
{
	char	*line;

	init(env);
	while (1)
	{
		if (init_prompt())
			continue ;
//		g_global.cmds = fake();
		parse();
		while (g_global.cmds)
		{
			g_global.cmds = g_global.cmds->next;
		}
		//exe(g_global.cmds);
	}
	return (0);
}