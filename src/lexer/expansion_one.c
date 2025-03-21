/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:35:08 by talin             #+#    #+#             */
/*   Updated: 2025/03/21 13:07:49 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int	single_dollar(char **ptr, char **output_ptr)
{
	char	*var_value;

	if (!**ptr || (!ft_is_valid_name_character(**ptr) && **ptr != '$'))
	{
		var_value = ft_strdup("$");
		get_value_copying(var_value, output_ptr);
		if (var_value)
			free(var_value);
		return (0);
	}
	if (**ptr && **ptr == '$')
	{
		var_value = ft_itoa(getpid());
		get_value_copying(var_value, output_ptr);
		if (var_value)
			free(var_value);
		(*ptr)++;
	}
	return (0);
}

static void	exit_status_util(t_data *data, char **output_ptr, char **var_name)
{
	int		i;
	char	*var_value;

	var_value = ft_itoa(data->status);
	get_value_copying(var_value, output_ptr);
	if (var_value)
		free(var_value);
	if ((*var_name)[1])
	{
		i = 1;
		while ((*var_name)[i])
		{
			**output_ptr = (*var_name)[i];
			(*output_ptr)++;
			i++;
		}
	}
	free(*var_name);
}

void	get_value(char **ptr, t_data *data, char **output_ptr)
{
	char	*var_name;
	int		var_index;
	char	*var_value;

	if (!ptr || !*ptr)
		return ;
	(*ptr)++;
	var_index = 0;
	while (**ptr && ft_is_valid_name_character(**ptr))
	{
		var_index++;
		(*ptr)++;
	}
	if (var_index == 0)
		if (single_dollar(ptr, output_ptr) == 0)
			return ;
	var_name = ft_strndup(*ptr - var_index, var_index);
	if (!var_name)
		return ;
	if (var_name[0] == '?')
		return (exit_status_util(data, output_ptr, &var_name));
	var_value = get_env_value(data->env, var_name);
	free(var_name);
	get_value_copying(var_value, output_ptr);
}
