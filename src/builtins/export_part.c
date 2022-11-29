/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:00:28 by acouliba          #+#    #+#             */
/*   Updated: 2022/11/29 19:00:31 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static t_bool	part(t_list *temp, char *key,
					  char *value, t_bool is_in_export)
{
	t_entry	*entry;

	entry = to_entry(temp->content);
	if (ft_strncmp(key, entry->key, ft_strlen(entry->key) + 1) == 0)
	{
		ft_putstr_fd(key, 2);
		free(key);
		if (value == NULL && entry->value != NULL)
			entry->is_exported = is_in_export;
		if (value == NULL)
			return (true);
		if (entry->value)
			free(entry->value);
		entry->value = value;
		return (true);
	}
	return (false);
}


static void	part1(char *key, char *value, t_bool is_in_export)
{
	t_entry	*entry;

	entry = malloc(sizeof(*entry));
	if (entry == NULL)
		return ;
	entry->key = key;
	entry->is_exported = is_in_export;
	entry->value = value;
	ft_lstadd_back(&g_global.entries, ft_lstnew(entry));
}


//[a-zA-Z_][a-zA-Z0-9_]
void	export_value(char *key, char *value, t_cmd *cmd,
					 t_bool is_in_export)
{
	t_list	*temp;
	t_bool	is_in;

	if (key == NULL)
		return ;
	is_in = false;
	temp = g_global.entries;
	while (temp)
	{
		is_in = part(temp, key, value, is_in_export);
		if (is_in == true)
			break ;
		temp = temp->next;
	}
	if (is_in == false)
		part1(key, value, is_in_export);
	update_env();
}

char	*get_key_cmd(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}

char	*get_value_cmd(char *str)
{
	int		i;
	char	*value;
	char	*temp;
	char	*sub;

	temp = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			sub = get_key_cmd(str);
			temp = ft_get_env(sub);
			free(sub);
		}
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	sub = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (temp == NULL)
		value = sub;
	else
	{
		value = ft_strjoin(temp, sub);
		free(temp);
		free(sub);
	}
	return (value);
}