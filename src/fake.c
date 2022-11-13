//
// Created by Abdoul Kader on 13/11/2022.
//

#include "../includes/header.h"

static t_cmd	*fake_cat2()
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * 4);
	cmd->args[0] = ft_strdup("head");
	cmd->args[1] = ft_strdup("-c");
	cmd->args[2] = ft_strdup("40");
	cmd->args[3] = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	cmd->path = NULL;
	return (cmd);
}

static t_cmd	*fake_cat()
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * 3);
	cmd->args[0] = ft_strdup("cat");
	cmd->args[1] = ft_strdup("-e");
	cmd->args[2] = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	cmd->next = fake_cat2();
	cmd->path = NULL;
	return (cmd);
}

t_cmd	*fake()
{
//	return (fake_cat());
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup("cat");
//	cmd->args[1] = ft_strdup("-l");
	cmd->args[1] = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = fake_cat();
	cmd->next = fake_cat2();
//	cmd->next = NULL;
	cmd->path = NULL;
	return (cmd);
}