/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:54:59 by talin             #+#    #+#             */
/*   Updated: 2025/02/18 16:43:29 by talin            ###   ########.fr       */
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

	if (!ptr || !*ptr)
		return ;
	(*ptr)++;
	if (!*ptr)
		return ;
	var_index = 0;
	while (*ptr && ft_is_valid_name_character(**ptr))
	{
		var_index++;
		(*ptr)++;
	}
	if (var_index == 0)
		return ;
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

size_t	calculate_expanded_size(const char *input, char **env)
{
	size_t		new_size;
	const char	*ptr;
	size_t		var_len;
	char		*var_name;
	char		*var_value;

	new_size = 1;
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '$')
		{
			ptr++;
			var_len = 0;
			while (ft_is_valid_name_character(*ptr))
			{
				var_len++;
				ptr++;
			}
			if (var_len > 0)
			{
				var_name = ft_strndup(ptr - var_len, var_len);
				if (!var_name)
					return (-1);
				var_value = get_env_value(env, var_name);
				free(var_name);
				if(var_value)
					new_size += ft_strlen(var_value);
			}
			continue ;
		}
		new_size++;
		ptr++;
	}
	return (new_size);
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

	if (!input)
		return (NULL);
	inside_double_quote = calculate_expanded_size(input, env);
	if (inside_double_quote == -1)
		return (NULL);
	expanded_str = malloc(inside_double_quote + 1);
	if (!expanded_str)
		return (perror("malloc"), NULL);
	ptr = input;
	output_ptr = expanded_str;
	inside_single_quote = 0;
	inside_double_quote = 0;
	while (ptr && *ptr != '\0')
	{
		if (*ptr == '\'' || *ptr == '\"')
			ft_quote_handle(&ptr, &output_ptr, \
			&inside_single_quote, &inside_double_quote);
		if (*ptr == '$' && !inside_single_quote)
		{
			get_value(&ptr, env, &output_ptr);
			if (!ptr || !*ptr)
				break ;
		}
		else
			*output_ptr++ = *ptr++;
	}
	*output_ptr = '\0';
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
	printf("after expandsion.....................\n");
	while (tokens->tokens[++i])
	{
		printf("%s\n", tokens->tokens[i]);
	}
	return (1);
}
