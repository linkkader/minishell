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

void free_tfile(t_file *tFile)
{
	t_file *temp;

	if (tFile == NULL)
		return ;
	while (tFile)
	{
		temp = tFile;
		tFile = tFile->next;
		free(temp->name);
		free(temp);
	}
}

static void clear()
{
	t_cmd*	temp;
	t_cmd*	temp2;

	free(g_global.line);
	g_global.line = NULL;
	temp = g_global.cmds;
//	return;
	while (temp)
	{
		free(temp->path);

		if (temp->cmd != NULL)
			clear_d2(temp->cmd);
		free(temp->cmd);
        temp->cmd = NULL;
		free_tfile(temp->file);
		temp2 = temp;
		temp = temp->next;
		free(temp2);
		temp2 = NULL;
	}
	free(temp);
	g_global.cmds = NULL;
}

int main(int ac, char **av, char **env)
{
	char	*line;
	t_global *tmp;
	int i = 0;

	tmp = &g_global;
	init(env);
	while (1)
	{
		if (init_prompt())
			continue ;
//		g_global.cmds = fake();
		g_global.exit_code = 0;
		parse();
//		while (1);
		 t_cmd *tmp = g_global.cmds;


		if (g_global.cmds)
			exe(g_global.cmds);
//       while (tmp != NULL)
//        {
//            for(int i=0; tmp->cmd[i] ; i++)
//                printf("%d %s\n", i, tmp->cmd[i]);
//            // printf("%s\n", tmp->cmd);
//            tmp = tmp->next;
//        }
		clear();

	}
	return (0);
}