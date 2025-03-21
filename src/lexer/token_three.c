/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:04:57 by talin             #+#    #+#             */
/*   Updated: 2025/03/14 10:38:40 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tokenize_three(char *input, int *i, int *in_quotes)
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

int	ft_tokenize_three(t_lexer **lexer, char *input, int *i, t_data *data)
{
	int		start;
	char	*token;
	int		in_quotes;

	start = *i;
	in_quotes = 0;
	tokenize_three(input, i, &in_quotes);
	if (in_quotes)
	{
		data->status = 2;
		ft_putendl_fd("minishell: unclosed quote", 2);
		free_lexer(*lexer);
		*lexer = NULL;
		return (0);
	}
	if (start < *i)
	{
		token = ft_strndup(input + start, *i - start);
		if (!token)
			return (free_lexer(*lexer), *lexer = NULL, 0);
		token[ft_strlen(token)] = '\0';
		add_token(lexer, TKN_WORD, token);
	}
	return (1);
}
