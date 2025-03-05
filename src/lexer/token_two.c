/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:06:22 by talin             #+#    #+#             */
/*   Updated: 2025/03/05 13:52:41 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	tokenize_two_token(char *input, int *i, int *in_quotes)
{
	char	quote_char;

	quote_char = '\0';
	while (input[*i])
	{
		if ((input[*i] == '"' || input[*i] == '\'')
			&& (!(*in_quotes) || input[*i] == quote_char))
		{
			if (!(*in_quotes))
			{
				(*in_quotes) = 1;
				quote_char = input[*i];
			}
			else
				(*in_quotes) = 0;
		}
		else if (!(*in_quotes) && (ft_isspace(input[*i]) || input[*i] == '|'
				|| input[*i] == '>' || input[*i] == '<'))
			break ;
		(*i)++;
	}
}

static int	tokenize_two_copy(char *input, int start, int *i, char **token)
{
	char	*combined;
	char	*temp;

	combined = ft_strndup(input + start, *i - start);
	if (!combined)
	{
		free((*token));
		return (0);
	}
	temp = ft_strjoin((*token), combined);
	free((*token));
	free(combined);
	(*token) = temp;
	return (1);
}

static char	*ft_tokenize_two_token(int start, int *i, char *input)
{
	char	*token;
	int		in_quotes;

	token = ft_strndup(input + start, *i - start + 1);
	if (!token)
		return (NULL);
	(*i)++;
	start = *i;
	in_quotes = 0;
	tokenize_two_token(input, i, &in_quotes);
	if (in_quotes)
	{
		perror("Unclosed quote");
		free(token);
		return (NULL);
	}
	if (start < *i)
	{
		if (tokenize_two_copy(input, start, i, &token) == 0)
			return (NULL);
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
