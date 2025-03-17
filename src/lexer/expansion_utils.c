/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:43:47 by juhtoo-h          #+#    #+#             */
/*   Updated: 2025/03/17 11:40:55 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_contain_dollar_sign(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*get_env_value(char *env[], const char *var_name)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (strncmp(env[i], var_name, strlen(var_name)) == 0 && \
		env[i][strlen(var_name)] == '=')
			return (&env[i][strlen(var_name) + 1]);
	}
	return (NULL);
}

int	ft_is_valid_name_character(const char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || \
	(c >= '0' && c <= '9') || c == '_' || c == '?')
		return (1);
	return (0);
}

int	empty_or_not(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (!ft_isspace(token[i]))
			return (1);
		i++;
	}
	return (0);
}
