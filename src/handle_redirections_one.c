/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_one.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:54:04 by rick              #+#    #+#             */
/*   Updated: 2025/03/03 14:41:31 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char	*env_value(t_data *data, const char *key)
{
	t_envp	*current;

	if (!key)
		return (NULL);
	current = data->envp;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (getenv(key));
}

void	error_file_not_found(char *path, t_data *data)
{
	ft_putstr_fd("minishell: file not found: ", STDERR_FILENO);
	if (path)
		ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->status = 1;
}

char	*expand_var_two(const char **pointer, t_data *data)
{
	char	*key;
	char	*value;

	key = env_name(pointer);
	if (!key)
	{
		error_syntax("$", data);
		return (ft_strdup("$"));
	}
	if (ft_strcmp(key, "?") == 0)
	{
		value = ft_itoa(data->status);
		free(key);
		return (value);
	}
	value = env_value(data, key);
	if (!value)
	{
		error_file_not_found(key, data);
		return (ft_strdup(""));
	}
	free(key);
	return (ft_strdup(value));
}

char	*expand_exit(t_data *data)
{
	char	*status;

	status = ft_itoa(data->status);
	if (!status)
	{
		error_malloc(data);
		return (NULL);
	}
	return (status);
}

char	*expand_single(const char **string, t_data *data)
{
	char	*result;

	if (!string || !*string || !**string)
	{
		error_eof("", data);
		return (NULL);
	}
	if (**string == '$')
	{
		if (*(*string + 1) == '?')
		{
			(*string += 2);
			return (expand_exit(data));
		}
		else
			return (expand_var_two(string, data));
	}
	result = ft_strndup(*string, 1);
	if (!result)
		return (NULL);
	result[0] = **string;
	result[1] = '\0';
	(*string)++;
	return (result);
}
