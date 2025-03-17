/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:48:31 by rick              #+#    #+#             */
/*   Updated: 2025/03/05 13:53:41 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_malloc(t_data *data)
{
	ft_putstr_fd("minishell: memory allocation failed\n", STDERR_FILENO);
	data->status = 1;
	(void)exit(data->status);
}

void	error_eof(char *token, t_data *data)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
		STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	data->status = 2;
}

char	*env_name(const char **input)
{
	const char	*start;
	const char	*end;

	while (**input == '$')
		(*input)++;
	start = *input;
	end = start;
	while (*end && (ft_isalnum(*end) || *end == '_'
			|| *end == '-' || *end == '.'))
		end++;
	if (start == end)
		return (NULL);
	*input = end;
	return (ft_strndup(start, end - start));
}

void	error_syntax(char *token, t_data *data)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (token && *token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	data->status = 2;
}
