/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:32:25 by talin             #+#    #+#             */
/*   Updated: 2025/03/19 21:37:31 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expand_var(char **cmd, t_data *data, t_lexer **lexer, int *status)
{
	char	*expanded_cmd;

	expanded_cmd = expand_variable(*cmd, data);
	if (strcmp(expanded_cmd, *cmd) != 0 && !ft_strchr(expanded_cmd, '\"')
		&& !ft_strchr(expanded_cmd, '\''))
		*status = 1;
	if (ft_contain_dollar_sign(*cmd) && ft_is_empty(expanded_cmd))
	{
		*status = 2;
		free(expanded_cmd);
		(*lexer)->error = 1;
		return (1);
	}
	if (expanded_cmd)
	{
		free(*cmd);
		*cmd = expanded_cmd;
		return (1);
	}
	else
		return (0);
}

void	ft_quote_handle(char **ptr, int *inside_single_quote,
		int *inside_double_quote)
{
	if (**ptr == '\'' && !(*inside_double_quote))
		*inside_single_quote = !(*inside_single_quote);
	if (**ptr == '\"' && !(*inside_single_quote))
		*inside_double_quote = !(*inside_double_quote);
}

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
