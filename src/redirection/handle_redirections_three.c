/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_three.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:53:30 by rick              #+#    #+#             */
/*   Updated: 2025/03/05 13:53:33 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_append(char *result, char *expanded, t_data *data)
{
	char	*new;

	new = ft_strjoin(result, expanded);
	free(expanded);
	free(result);
	if (!new)
		error_malloc(data);
	return (new);
}

char	*quote_expand(char *string, t_data *data)
{
	char	*result;
	char	*expanded;

	if (!string)
		return (error_eof("", data), NULL);
	result = ft_strdup("");
	if (!result)
		error_malloc(data);
	while (*string)
	{
		expanded = expand_single((const char **)&string, data);
		if (!expanded)
		{
			free(result);
			return (NULL);
		}
		result = expand_append(result, expanded, data);
		if (!result)
			return (NULL);
	}
	return (result);
}

void	error_delimeter(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line 1 \
		delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')", STDERR_FILENO);
	rl_clear_history();
}

int	delimeter_content(t_io_file *delimeter)
{
	delimeter->content = ft_strdup("");
	if (!delimeter->content)
	{
		ft_error("delimeter: memory allocation failed");
		return (0);
	}
	return (1);
}

int	delimeter_append(t_io_file *delimeter, char *line)
{
	char	*temp;
	char	*append;

	if (!delimeter->content)
		return (0);
	if (delimeter->content[0] == '\0')
		temp = ft_strdup(line);
	else
	{
		temp = ft_strjoin(delimeter->content, "\n");
		if (!temp)
		{
			ft_error("delimeter: memory allocation failed");
			return (0);
		}
		append = ft_strjoin(temp, line);
		free(temp);
		temp = append;
	}
	if (!temp)
		return (ft_error("delimeter: memory allocation failed"), 0);
	free(delimeter->content);
	delimeter->content = temp;
	return (1);
}
