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
	cmd->files = NULL;
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
	cmd->files = NULL;
	cmd->next = NULL;
	cmd->next = fake_cat2();
	cmd->path = NULL;
	return (cmd);
}

static t_file *fake_outfile(char *name)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	file->token = OUTFILE;
	file->next = NULL;
	return (file);
}

static t_file *fake_append(char *name)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	file->token = INFILE;
	file->next = NULL;
	return (file);
}

static t_file *fake_infile(char *name)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	file->token = INFILE;
	file->next = NULL;
	return (file);
}

static t_file *fake_heredoc(char *name)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	file->token = HEREDOC;
	file->next = NULL;
	return (file);
}

t_file *fake_file()
{
	t_file	*file = fake_infile("Makefile");
	file->next = fake_infile("in.txt");
	file->next->next = fake_outfile("out.txt");
	file->next->next->next = fake_outfile("out2.txt");
	file->next->next->next->next = fake_heredoc("ll");
	return (file);
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
	cmd->files = fake_file();
	cmd->next = fake_cat();
	cmd->next = fake_cat2();
	cmd->next = NULL;
	cmd->path = NULL;
	return (cmd);
}