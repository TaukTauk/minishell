/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:32:24 by juhtoo-h          #+#    #+#             */
/*   Updated: 2025/03/17 12:33:06 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_unclosed_quotes(const char *token)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = -1;
	while (token[++i])
	{
		if (token[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (token[i] == '"' && single_quote == 0)
			double_quote = !double_quote;
	}
	return (single_quote || double_quote);
}

int	is_metacharacter(t_lexer *token)
{
	return (token->token_type == TKN_IN
		|| token->token_type == TKN_OUT
		|| token->token_type == TKN_RDAPPEND
		|| token->token_type == TKN_RDHEREDOC
		|| token->token_type == TKN_PIPE);
}

int	is_valid_redirection(t_lexer *token, t_lexer *next_token)
{
	if (token->token_type == TKN_IN
		|| token->token_type == TKN_OUT
		|| token->token_type == TKN_RDAPPEND
		|| token->token_type == TKN_RDHEREDOC)
	{
		if (!next_token || !next_token->value
			|| next_token->value[0] == '\0'
			|| next_token->token_type == TKN_PIPE
			|| is_metacharacter(next_token))
			return (0);
	}
	return (1);
}
