/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:02:22 by juhtoo-h          #+#    #+#             */
/*   Updated: 2025/03/21 13:57:17 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	question_mark(t_data *data, size_t *new_size, char **var_name)
{
	char	*status_str;

	status_str = ft_itoa(data->status);
	if (status_str)
	{
		*new_size += ft_strlen(status_str);
		free(status_str);
	}
	if ((*var_name)[1])
		*new_size += ft_strlen(*var_name) - 1;
	free(*var_name);
}

static void	dollar_sign(size_t *new_size, const char **ptr)
{
	char	*pid_str;

	pid_str = ft_itoa(getpid());
	if (pid_str)
	{
		*new_size += ft_strlen(pid_str);
		free(pid_str);
	}
	(*ptr)++;
}

static int	variable_name(t_data *data, size_t *new_size,
	size_t *var_len, const char **ptr)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_strndup(*ptr - *var_len, *var_len);
	if (!var_name)
		return (-1);
	if (var_name[0] == '?')
	{
		question_mark(data, new_size, &var_name);
		return (1);
	}
	var_value = get_env_value(data->env, var_name);
	if (var_value)
		*new_size += ft_strlen(var_value);
	free(var_name);
	return (1);
}

static int	dollar_sign_expand(size_t *new_size, const char **ptr, t_data *data)
{
	size_t	var_len;

	if (!(**ptr))
	{
		(*new_size)++;
		return (-1);
	}
	if (**ptr == '$')
	{
		dollar_sign(new_size, ptr);
		return (1);
	}
	var_len = 0;
	while (**ptr && ft_is_valid_name_character(**ptr))
	{
		var_len++;
		(*ptr)++;
	}
	if (var_len == 0)
	{
		(*new_size)++;
		return (1);
	}
	return (variable_name(data, new_size, &var_len, ptr));
}

size_t	calculate_expanded_size(const char *input, t_data *data)
{
	size_t		new_size;
	const char	*ptr;
	int			single_quote;
	int			double_quote;

	single_quote = 0;
	double_quote = 0;
	new_size = 0;
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '\'')
			ft_quote_handle_size(ptr, &single_quote, &double_quote);
		if (*ptr == '$' && !single_quote)
		{
			ptr++;
			if (dollar_sign_expand(&new_size, &ptr, data) == -1)
				break ;
			else
				continue ;
		}
		increasing_size(&new_size, &ptr, double_quote, single_quote);
	}
	return (new_size + 1);
}
