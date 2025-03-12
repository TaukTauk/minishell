/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:54:59 by talin             #+#    #+#             */
/*   Updated: 2025/03/12 20:48:10 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_variable_copy(char **ptr, t_data *data, char **output_ptr)
{
	int	inside_single_quote;
	int	inside_double_quote;

	inside_single_quote = 0;
	inside_double_quote = 0;
	while (*ptr && **ptr != '\0')
	{
		if (**ptr == '\'' || **ptr == '\"')
			ft_quote_handle(ptr, &inside_single_quote, &inside_double_quote);
		if (**ptr == '$' && !inside_single_quote)
		{
			get_value(ptr, data, output_ptr);
			if (!*ptr || !**ptr)
				break ;
			continue ;
		}
		if (**ptr)
			*(*output_ptr)++ = *(*ptr)++;
	}
	*(*output_ptr) = '\0';
}

char	*expand_variable(char *input, t_data *data)
{
	char	*expanded_str;
	char	*ptr;
	char	*output_ptr;
	int		size;

	if (!input)
		return (NULL);
	size = calculate_expanded_size(input, data);
	if (size == -1)
		return (NULL);
	expanded_str = malloc(size + 1);
	if (!expanded_str)
		return (perror("malloc"), NULL);
	ptr = input;
	output_ptr = expanded_str;
	expand_variable_copy(&ptr, data, &output_ptr);
	return (expanded_str);
}

int	expand_var(char **cmd, t_data *data)
{
	char	*expanded_cmd;

	expanded_cmd = expand_variable(*cmd, data);
	if (expanded_cmd)
	{
		free(*cmd);
		*cmd = expanded_cmd;
		return (1);
	}
	else
		return (0);
}

int	parameter_expansion(t_lexer *tokens, t_data *data)
{
	int		i;

	i = -1;
	if (!tokens)
		return (0);
	while (tokens->tokens[++i])
	{
		if (i >= 1 && ft_strcmp(tokens->tokens[i - 1], "<<") == 0)
			continue ;
		if (!expand_var(&(tokens->tokens[i]), data))
			return (0);
	}
	i = -1;
	while (tokens->tokens[++i])
		remove_quote(&(tokens->tokens[i]));
	return (1);
}
