/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:50:51 by talin             #+#    #+#             */
/*   Updated: 2025/03/03 14:36:55 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_token(t_lexer *lexer, char *token)
{
	char	**new_tokens;
	int		i;

	new_tokens = malloc(sizeof(char *) * (lexer->token_count + 1));
	if (!new_tokens)
	{
		perror("malloc");
		exit (EXIT_FAILURE);
	}
	i = -1;
	while (++i < lexer->token_count)
		new_tokens[i] = lexer->tokens[i];
	new_tokens[lexer->token_count] = token;
	free(lexer->tokens);
	lexer->tokens = new_tokens;
	lexer->token_count++;
}

int	ft_tokenize_one(t_lexer *lexer, char *input, int *i)
{
	char	*token;

	if (input[(*i + 1)] && ((input[*i] == '>' && input[(*i + 1)] == '>') || \
	(input[*i] == '<' && input[(*i + 1)] == '<')))
	{
		token = malloc(3);
		if (!token)
			return (free_lexer(lexer), 0);
		token[0] = input[(*i)++];
		token[1] = input[(*i)++];
		token[2] = '\0';
		add_token(lexer, token);
	}
	else
	{
		token = malloc(2);
		if (!token)
			return (free_lexer(lexer), 0);
		token[0] = input[(*i)++];
		token[1] = '\0';
		add_token(lexer, token);
	}
	return (1);
}

char	*ft_tokenize_two_token(int start, int *i, char *input)
{
	char	*token;
	char	*combined;
	char	*temp;
	int		in_quotes;
	char	quote_char;

	token = ft_strndup(input + start, *i - start + 1);
	if (!token)
		return (NULL);
	(*i)++;
	start = *i;
	in_quotes = 0;
	quote_char = '\0';
	while (input[*i])
	{
		if ((input[*i] == '"' || input[*i] == '\'')
			&& (!in_quotes || input[*i] == quote_char))
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = input[*i];
			}
			else
				in_quotes = 0;
		}
		else if (!in_quotes && (ft_isspace(input[*i]) || input[*i] == '|'
				|| input[*i] == '>' || input[*i] == '<'))
			break ;
		(*i)++;
	}
	if (in_quotes)
	{
		perror("Unclosed quote");
		free(token);
		return (NULL);
	}
	if (start < *i)
	{
		combined = ft_strndup(input + start, *i - start);
		if (!combined)
		{
			free(token);
			return (NULL);
		}
		temp = ft_strjoin(token, combined);
		free(token);
		free(combined);
		token = temp;
	}
	token[ft_strlen(token)] = '\0';
	return (token);
}

int	ft_tokenize_two(t_lexer *lexer, char *input, int *i)
{
	char	*token;
	char	quote;
	int		start;

	quote = input[(*i)];
	start = *i;
	if (input[(*i) + 1])
		(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
	{
		token = ft_tokenize_two_token(start, i, input);
		if (!token)
			return (free_lexer(lexer), 0);
		add_token(lexer, token);
	}
	else
	{
		perror("unclosed quote");
		free_lexer(lexer);
		return (0);
	}
	return (1);
}

int	ft_tokenize_three(t_lexer *lexer, char *input, int *i)
{
	int		start;
	char	*token;
	int		in_quotes;
	char	quote_char;

	start = *i;
	in_quotes = 0;
	quote_char = '\0';
	while (input[*i])
	{
		if ((input[*i] == '"' || input[*i] == '\'')
			&& (!in_quotes || input[*i] == quote_char))
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = input[*i];
			}
			else
				in_quotes = 0;
		}
		else if (!in_quotes && (ft_isspace(input[*i]) || input[*i] == '|'
				|| input[*i] == '>' || input[*i] == '<'))
			break ;
		(*i)++;
	}
	if (in_quotes)
	{
		perror("Unclosed quote");
		free_lexer(lexer);
		return (0);
	}
	if (start < *i)
	{
		token = ft_strndup(input + start, *i - start);
		if (!token)
			return (free_lexer(lexer), 0);
		token[ft_strlen(token)] = '\0';
		add_token(lexer, token);
	}
	return (1);
}

int	ft_tokenize_four(t_lexer *lexer, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (!ft_tokenize_one(lexer, input, &i))
				return (0);
			continue ;
		}
		if (input[i] == '"' || input[i] == '\'')
		{
			if (!ft_tokenize_two(lexer, input, &i))
				return (0);
			continue ;
		}
		if (!ft_tokenize_three(lexer, input, &i))
			return (0);
	}
	return (1);
}
