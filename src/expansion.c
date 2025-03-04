/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:54:59 by talin             #+#    #+#             */
/*   Updated: 2025/03/04 10:38:57 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_variable_copy(char **ptr, char **env, char **output_ptr)
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
			get_value(ptr, env, output_ptr);
			if (!*ptr || !**ptr)
				break ;
			continue ;
		}
		if (**ptr)
			*(*output_ptr)++ = *(*ptr)++;
	}
	*(*output_ptr) = '\0';
}

char	*expand_variable(char *input, char **env)
{
	char	*expanded_str;
	char	*ptr;
	char	*output_ptr;
	int		size;

	if (!input)
		return (NULL);
	size = calculate_expanded_size(input, env);
	if (size == -1)
		return (NULL);
	expanded_str = malloc(size + 1);
	if (!expanded_str)
		return (perror("malloc"), NULL);
	ptr = input;
	output_ptr = expanded_str;
	expand_variable_copy(&ptr, env, &output_ptr);
	return (expanded_str);
}

int	expand_var(char **cmd, char **env)
{
	char	*expanded_cmd;

	expanded_cmd = expand_variable(*cmd, env);
	if (expanded_cmd)
	{
		free(*cmd);
		*cmd = expanded_cmd;
		return (1);
	}
	else
		return (0);
}

int	parameter_expansion(t_lexer *tokens, char **env)
{
	int		i;

	i = -1;
	while (tokens->tokens[++i])
	{
		if (i >= 1 && ft_strcmp(tokens->tokens[i - 1], "<<") == 0)
			continue ;
		if (!expand_var(&(tokens->tokens[i]), env))
			return (0);
	}
	i = -1;
	while (tokens->tokens[++i])
		remove_quote(&(tokens->tokens[i]));
	return (1);
}
