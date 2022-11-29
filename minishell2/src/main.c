/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:12:48 by acouliba          #+#    #+#             */
/*   Updated: 2022/11/29 17:12:51 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	reset(void )
{
	normal_echo();
}

static int	init_prompt(void)
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

void	free_tfile(t_file *tFile)
{
	t_file	*temp;

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

static void	clear(void)
{
	t_cmd	*temp;
	t_cmd	*temp2;

	free(g_global.line);
	g_global.line = NULL;
	temp = g_global.cmds;
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

int	main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		ft_putendl_fd("error", 2);
		return (1);
	}
	init(env);
	while (1)
	{
		if (init_prompt())
			continue ;
		parse();
		system("leaks minishell");
		if (g_global.cmds)
			exe(g_global.cmds);
		clear();
	}
	return (0);
}

//		while (g_global.cmds)
//		{
//			int 	i;
//
//			i = 0;
//			while (g_global.cmds->cmd[i])
//			{
//				printf("%s\n", g_global.cmds->cmd[i]);
//				i++;
//			}
//			g_global.cmds = g_global.cmds->next;
//		}
