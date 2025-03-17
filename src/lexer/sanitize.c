/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:32:21 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/17 12:44:10 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_redirection(t_lexer *current, t_lexer *next,
	t_data *data, t_lexer *lexer)
{
	if (current->token_type == TKN_IN || current->token_type == TKN_OUT
		|| current->token_type == TKN_RDAPPEND
		|| current->token_type == TKN_RDHEREDOC)
	{
		if (!is_valid_redirection(current, next))
		{
			data->status = 2;
			ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
			write(2, current->value, ft_strlen(current->value));
			write(2, "'\n", 2);
			return (free_lexer(lexer), data->lexer = NULL,
				ERROR_INVALID_REDIRECTION);
		}
	}
	return (0);
}

static int	check_pipe(t_lexer *current, t_lexer *next,
	t_lexer *lexer, t_data *data)
{
	if (current->token_type == TKN_PIPE)
	{
		if (current == lexer || !next || next->token_type == TKN_PIPE)
		{
			data->status = 2;
			ft_putendl_fd
				("minishell: syntax error near unexpected token '|'", 2);
			return (free_lexer(lexer),
				data->lexer = NULL, ERROR_INVALID_PIPE);
		}
	}
	return (0);
}

int	sanitize_tokens(t_lexer *lexer, t_data *data)
{
	t_lexer	*current;
	t_lexer	*next;

	if (!lexer)
		return (1);
	current = lexer;
	while (current)
	{
		if (check_unclosed_quotes(current->value))
		{
			data->status = 2;
			ft_putendl_fd("minishell: unclosed quote", 2);
			return (free_lexer(lexer), data->lexer = NULL, ERROR_INVALID_QUOTE);
		}
		next = current->next;
		if (check_redirection(current, next, data, lexer) != 0)
			return (ERROR_INVALID_REDIRECTION);
		if (check_pipe(current, next, lexer, data) != 0)
			return (ERROR_INVALID_PIPE);
		current = next;
	}
	return (0);
}
