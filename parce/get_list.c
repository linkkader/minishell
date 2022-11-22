/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:12:11 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/21 23:42:02 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	free_matrix(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_strlen_(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return 0;
	while (tab[i])
		i++;
	return (i);
}

char	**store_cmd(char **tab, char *str)
{
	char	**new;
	int		i;

	i = 0;
	if (!str)
		return (tab);
	if (!tab)
	{
		new = malloc(2 * sizeof(char *));
		new[0] = ft_strdup_parse(str);
		new[1] = NULL;
	}
	else
	{
		new = malloc((ft_strlen_(tab) + 2) * sizeof(char *));
		while (tab[i])
		{
			new[i] = ft_strdup_parse(tab[i]);
			i++;
		}
		new[i++] = ft_strdup_parse(str);
		new[i] = NULL;
	}
	if (tab)
		free_matrix(tab);
	return (new);
}

void	store_file(t_cmd *data, int i, char *content)
{
	if (i == 2)
		ft_lstadd_back_parse(&data->file, ft_lstnew_parse(2, content));
	else if (i == 4)
		ft_lstadd_back_parse(&data->file, ft_lstnew_parse(4, content));
	else if (i == 0)
		ft_lstadd_back_parse(&data->file, ft_lstnew_parse(0, content));
	else if (i == 1)
		ft_lstadd_back_parse(&data->file, ft_lstnew_parse(1, content));
	else
	{
		data->cmd = store_cmd(data->cmd, content);
	}
		
}