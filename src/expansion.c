/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:54:59 by talin             #+#    #+#             */
/*   Updated: 2025/02/17 16:46:15 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(char *env[], const char *var_name)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (strncmp(env[i], var_name, strlen(var_name)) == 0 && \
		env[i][strlen(var_name)] == '=')
			return (&env[i][strlen(var_name) + 1]);
	}
	return (NULL);
}

int	ft_is_valid_name_character(const char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || \
	(c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

void	get_value(char **ptr, char **env, char **output_ptr)
{
	char	*var_name;
	int		var_index;
	char	*var_value;

	(*ptr)++;
	var_index = 0;
	while (ft_is_valid_name_character(**ptr))
	{
		var_index++;
		(*ptr)++;
	}
	var_name = ft_strndup(*ptr - var_index, var_index);
	if (!var_name)
		return ;
	var_value = get_env_value(env, var_name);
	free(var_name);
	if (var_value)
	{
		while (*var_value)
		{
			**output_ptr = *var_value;
			(*output_ptr)++;
			var_value++;
		}
	}
}

void	ft_quote_handle(char **ptr, char **output_ptr, \
int *inside_single_quote, int *inside_double_quote)
{
	if (**ptr == '\'' && !(*inside_double_quote))
	{
		*inside_single_quote = !(*inside_single_quote);
		**output_ptr = **ptr;
		(*output_ptr)++;
		(*ptr)++;
	}
	if (**ptr == '\"' && !(*inside_single_quote))
	{
		*inside_double_quote = !(*inside_double_quote);
		**output_ptr = **ptr;
		(*output_ptr)++;
		(*ptr)++;
	}
}

char	*expand_variable(char *input, char **env)
{
	char	*expanded_str;
	char	*ptr;
	char	*output_ptr;
	int		inside_single_quote;
	int		inside_double_quote;

	expanded_str = malloc(ft_strlen(input) + 1);
	if (!expanded_str)
		return (perror("malloc"), NULL);
	ptr = input;
	output_ptr = expanded_str;
	inside_single_quote = 0;
	inside_double_quote = 0;
	while (*ptr)
	{
		if (*ptr == '\'' || *ptr == '\"')
			ft_quote_handle(&ptr, &output_ptr, \
			&inside_single_quote, &inside_double_quote);
		if (*ptr == '$' && !inside_single_quote)
			get_value(&ptr, env, &output_ptr);
		else
			*output_ptr++ = *ptr++;
	}
	*output_ptr = '\0';
	return (expanded_str);
}

void	expand_var(char **cmd, char **env)
{
	char	*expanded_cmd;

	expanded_cmd = expand_variable(*cmd, env);
	if (expanded_cmd)
	{
		free(*cmd);
		*cmd = expanded_cmd;
	}
}

void	parameter_expansion(t_lexer *tokens, char **env)
{
	int		i;

	i = -1;
	while (tokens->tokens[++i])
	{
		expand_var(&(tokens->tokens[i]), env);
	}
}
