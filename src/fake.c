
#include "../includes/header.h"

static t_cmd	*fake_cat2()
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = malloc(sizeof(char *) * 4);
	cmd->cmd[0] = ft_strdup("head");
	cmd->cmd[1] = ft_strdup("-c");
	cmd->cmd[2] = ft_strdup("40");
	cmd->cmd[3] = NULL;
	cmd->file = NULL;
	cmd->next = NULL;
	cmd->path = NULL;
	return (cmd);
}

static t_cmd	*fake_cat()
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = malloc(sizeof(char *) * 3);
	cmd->cmd[0] = ft_strdup("cat");
	cmd->cmd[1] = ft_strdup("in.txt");
	cmd->cmd[2] = NULL;
	cmd->file = NULL;
//	cmd->next = fake_cat2();
	cmd->next = NULL;
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
	t_file	*file = fake_infile("in.txt");
//	file->next = fake_infile("in.txt");
//	file->next = fake_outfile("out.txt");
//	file->next->next->next = fake_outfile("out2.txt");
	file->next = fake_heredoc("ll");
	return (file);
}

t_cmd	*fake()
{
//	return (fake_cat());
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = malloc(sizeof(char *) * 2);
	cmd->cmd[0] = ft_strdup("cat");
//	cmd->cmd[1] = ft_strdup("-l");
	cmd->cmd[1] = NULL;
	cmd->file = fake_file();
	cmd->next = fake_cat();
//	cmd->next = fake_cat2();
//	cmd->next = NULL;
	cmd->path = NULL;
	return (cmd);
}