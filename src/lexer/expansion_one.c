/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:35:08 by talin             #+#    #+#             */
/*   Updated: 2025/03/12 21:18:45 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	(c >= '0' && c <= '9') || c == '_' || c == '?')
		return (1);
	return (0);
}

static void	get_value_copying(char *var_value, char **output_ptr)
{
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

void	get_value(char **ptr, t_data *data, char **output_ptr)
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
	{
		if (!**ptr || (!ft_is_valid_name_character(**ptr) && **ptr != '$'))
		{
			var_value = ft_strdup("$");
			get_value_copying(var_value, output_ptr);
			if (var_value)
				free(var_value);
			if (**ptr)
				(*ptr)++;
			return ;
		}
		if (**ptr && **ptr == '$')
		{
			var_value = ft_itoa(getpid());
			get_value_copying(var_value, output_ptr);
			if (var_value)
				free(var_value);
			(*ptr)++;
		}
		return ;
	}
	var_name = ft_strndup(*ptr - var_index, var_index);
	if (!var_name)
		return ;
	if (var_name[0] == '?')
	{
		var_value = ft_itoa(data->status);
		get_value_copying(var_value, output_ptr);
		if (var_value)
			free(var_value);
		if (var_name[1])
		{
			int	i = 1;
			while (var_name[i])
			{
				**output_ptr = var_name[i];
				(*output_ptr)++;
				i++;
			}
		}
		free(var_name);
		return ;
	}
	var_value = get_env_value(data->env, var_name);
	free(var_name);
	get_value_copying(var_value, output_ptr);
}

void	ft_quote_handle(char **ptr, int *inside_single_quote,
			int *inside_double_quote)
{
	if (**ptr == '\'' && !(*inside_double_quote))
		*inside_single_quote = !(*inside_single_quote);
	if (**ptr == '\"' && !(*inside_single_quote))
		*inside_double_quote = !(*inside_double_quote);
}
