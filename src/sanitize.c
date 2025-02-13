/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:32:21 by ubuntu            #+#    #+#             */
/*   Updated: 2025/01/20 13:44:30 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	is_metacharacter(const char *token)
{
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0 || \
	ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0 || \
	ft_strcmp(token, "|") == 0)
		return (1);
	return (0);
}

int	is_valid_redirection(const char *token, const char *next_token)
{
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 || \
	ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0)
	{
		if (!next_token || next_token[0] == '\0' || \
		ft_strcmp(next_token, "|") == 0 || is_metacharacter(next_token))
			return (0);
	}
	return (1);
}

int	sanitize_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (check_unclosed_quotes(tokens[i]))
			return (perror("Error: Unclosed quotes"), ERROR_INVALID_QUOTE);
		if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0 || \
		ft_strcmp(tokens[i], "<<") == 0 || ft_strcmp(tokens[i], ">>") == 0)
		{
			if (!is_valid_redirection(tokens[i], tokens[i + 1]))
				return (perror("Error: Invalid redirection"), \
				ERROR_INVALID_REDIRECTION);
		}
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			if (i == 0 || !tokens[i + 1] || ft_strcmp(tokens[i + 1], "|") == 0)
				return (perror("Error: Invalid pipe placement"), \
				ERROR_INVALID_PIPE);
		}
	}
	return (0);
}
