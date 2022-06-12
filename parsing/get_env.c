/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:59:28 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/04 18:42:20 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_ft_getenv(char *var, char **env)
{
	int		i;
	int		len;

	i = -1;
	len = parse_ft_strlen(var);
	while (env[++i])
		if (!parse_ft_strncmp(env[i], var, len) && env[i][len] == '=')
			return (parse_ft_strdup(env[i] + len + 1));
	return (NULL);
}
