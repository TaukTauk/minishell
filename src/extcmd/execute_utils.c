/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 08:26:28 by juhtoo-h          #+#    #+#             */
/*   Updated: 2025/03/17 09:30:41 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_getenv(char *name, char **envp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		str = ft_substr(envp[i], 0, j);
		if (ft_strcmp(str, name) == 0)
		{
			free(str);
			return (envp[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}

int	ft_check_set_unset(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0 && envp[i][4] == '=')
			return (1);
	}
	return (0);
}

void	free_command_lexer_in_exec(t_data *data)
{
	t_lexer	*tmp;
	t_lexer	*next;

	if (data->lexer)
	{
		tmp = data->lexer;
		while (tmp)
		{
			next = tmp->next;
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			tmp = next;
		}
	}
	if (data->commands)
	{
		free_command(data->commands);
	}
}

int	ft_check_exec_access(char *path)
{
	if (path)
	{
		if (access(path, X_OK) == 0)
			return (1);
		free(path);
		return (0);
	}
	return (0);
}
