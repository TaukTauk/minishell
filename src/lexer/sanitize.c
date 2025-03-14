/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:32:21 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/14 10:53:39 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	check_unclosed_quotes(const char *token)
// {
// 	int	single_quote;
// 	int	double_quote;
// 	int	i;

// 	single_quote = 0;
// 	double_quote = 0;
// 	i = -1;
// 	while (token[++i])
// 	{
// 		if (token[i] == '\'' && double_quote == 0)
// 			single_quote = !single_quote;
// 		else if (token[i] == '"' && single_quote == 0)
// 			double_quote = !double_quote;
// 	}
// 	return (single_quote || double_quote);
// }

// int	is_metacharacter(const char *token)
// {
// 	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0 || \
// 	ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0 || \
// 	ft_strcmp(token, "|") == 0)
// 		return (1);
// 	return (0);
// }

// int	is_valid_redirection(const char *token, const char *next_token)
// {
// 	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 || \
// 	ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0)
// 	{
// 		if (!next_token || next_token[0] == '\0' || \
// 		ft_strcmp(next_token, "|") == 0 || is_metacharacter(next_token))
// 			return (0);
// 	}
// 	return (1);
// }

// int	sanitize_tokens(char **tokens, t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	if (!(tokens && *tokens))
// 		return (1);
// 	while (tokens[++i])
// 	{
// 		if (check_unclosed_quotes(tokens[i]))
// 		{
// 			data->status = 2;
// 			return (ft_putendl_fd("minishell: unclosed quote", 2), ERROR_INVALID_QUOTE);
// 		}
// 		if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0 || \
// 		ft_strcmp(tokens[i], "<<") == 0 || ft_strcmp(tokens[i], ">>") == 0)
// 		{
// 			if (!is_valid_redirection(tokens[i], tokens[i + 1]))
// 			{
// 				data->status = 2;
// 				return (ft_putstr_fd("minishell: syntax error near unexpected token '", 2), write(2, tokens[i], ft_strlen(tokens[i])), write(2, "'\n", 2), \
// 				ERROR_INVALID_REDIRECTION);
// 			}
// 		}
// 		if (ft_strcmp(tokens[i], "|") == 0)
// 		{
// 			if (i == 0 || !tokens[i + 1] || ft_strcmp(tokens[i + 1], "|") == 0)
// 			{
// 				data->status = 2;
// 				return (ft_putendl_fd("minishell: syntax error near unexpected token '|'", 2), \
// 				ERROR_INVALID_PIPE);
// 			}
// 		}
// 	}
// 	return (0);
// }

int check_unclosed_quotes(const char *token)
{
    int single_quote;
    int double_quote;
    int i;

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

int is_metacharacter(t_lexer *token)
{
    return (token->token_type == TKN_IN || 
            token->token_type == TKN_OUT || 
            token->token_type == TKN_RDAPPEND || 
            token->token_type == TKN_RDHEREDOC || 
            token->token_type == TKN_PIPE);
}

int is_valid_redirection(t_lexer *token, t_lexer *next_token)
{
    if (token->token_type == TKN_IN || 
        token->token_type == TKN_OUT || 
        token->token_type == TKN_RDAPPEND || 
        token->token_type == TKN_RDHEREDOC)
    {
        if (!next_token || 
            !next_token->value || 
            next_token->value[0] == '\0' || 
            next_token->token_type == TKN_PIPE || 
            is_metacharacter(next_token))
            return (0);
    }
    return (1);
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
			return (ERROR_INVALID_QUOTE);
		}
		next = current->next;
		if (current->token_type == TKN_IN || 
			current->token_type == TKN_OUT || 
			current->token_type == TKN_RDAPPEND || 
			current->token_type == TKN_RDHEREDOC)
		{
			if (!is_valid_redirection(current, next))
			{
				data->status = 2;
				ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
				write(2, current->value, ft_strlen(current->value));
				write(2, "'\n", 2);
				return (ERROR_INVALID_REDIRECTION);
			}
		}
		if (current->token_type == TKN_PIPE)
		{
			if (current == lexer || !next || next->token_type == TKN_PIPE)
			{
				data->status = 2;
				ft_putendl_fd("minishell: syntax error near unexpected token '|'", 2);
				return (ERROR_INVALID_PIPE);
			}
		}
		current = next;
	}
	return (0);
}
