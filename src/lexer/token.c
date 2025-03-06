/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:50:51 by talin             #+#    #+#             */
/*   Updated: 2025/03/06 12:13:34 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token(t_lexer *lexer, char *token)
{
	char	**new_tokens;
	int		i;

	new_tokens = malloc(sizeof(char *) * (lexer->token_count + 1));
	if (!new_tokens)
	{
		ft_putendl_fd("minishell: malloc error for adding token", 2);
		return ;
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

int	ft_tokenize_four(t_lexer *lexer, char *input, t_data *data)
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

t_lexer	*tokenize(char *input, t_data *data)
{
	t_lexer	*lexer;
	char	**new_tokens;
	int		i;

	if (!input)
		return (NULL);
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->tokens = NULL;
	lexer->token_count = 0;
	if (!ft_tokenize_four(lexer, input, data))
		return (NULL);
	new_tokens = malloc(sizeof(char *) * (lexer->token_count + 1));
	if (!new_tokens)
		return (free_lexer(lexer), NULL);
	i = -1;
	while (++i < lexer->token_count)
		new_tokens[i] = lexer->tokens[i];
	free(lexer->tokens);
	lexer->tokens = new_tokens;
	lexer->tokens[lexer->token_count] = NULL;
	return (lexer);
}
