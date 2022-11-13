//
// Created by Abdoul Kader on 12/11/2022.
//

#include "../includes/header.h"

static	int init_prompt(void)
{
	g_global.line = readline(PROMPT_CMD);
	if (!g_global.line)
	{
		write(1, "exit\n", 5);
		exit(g_global.exit_code);
	}
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
		g_global.cmds = fake();
		exe(g_global.cmds);
	}
	return (0);
}