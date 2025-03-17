/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:42:52 by talin             #+#    #+#             */
/*   Updated: 2025/03/17 12:46:40 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_tokenize_one(t_lexer **lexer, char *input, int *i)
{
	char	*token;
	int		token_type;

	if (input[(*i + 1)] && ((input[*i] == '>' && input[(*i + 1)] == '>') || \
	(input[*i] == '<' && input[(*i + 1)] == '<')))
	{
		token = malloc(3);
		if (!token)
			return (free_lexer(*lexer), *lexer = NULL, 0);
		token[0] = input[(*i)++];
		token[1] = input[(*i)++];
		token[2] = '\0';
		token_type = get_token_type(token);
	}
	else
	{
		token = malloc(2);
		if (!token)
			return (free_lexer(*lexer), *lexer = NULL, 0);
		token[0] = input[(*i)++];
		token[1] = '\0';
		token_type = get_token_type(token);
	}
	add_token(lexer, token_type, token);
	return (1);
}

int	ft_tokenize_four(t_lexer **lexer, char *input, t_data *data)
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
			if (!ft_tokenize_two(lexer, input, &i, data))
				return (0);
			continue ;
		}
		if (!ft_tokenize_three(lexer, input, &i, data))
			return (0);
	}
	return (1);
}
