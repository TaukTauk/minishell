/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:32:25 by talin             #+#    #+#             */
/*   Updated: 2025/03/04 10:32:49 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expanded_size_ptr_increase(const char **ptr, size_t *var_len)
{
	(*ptr)++;
	(*var_len) = 0;
	while (ft_is_valid_name_character(**ptr))
	{
		(*var_len)++;
		(*ptr)++;
	}
}

static int	expanded_size_create_var(size_t *var_len, char **env, const char **ptr, size_t *new_size)
{
	char	*var_name;
	char	*var_value;

	if ((*var_len) > 0)
	{
		var_name = ft_strndup((*ptr) - (*var_len), (*var_len));
		if (!var_name)
			return (-1);
		var_value = get_env_value(env, var_name);
		free(var_name);
		if (var_value)
			(*new_size) += ft_strlen(var_value);
	}
	return (0);
}

size_t	calculate_expanded_size(const char *input, char **env)
{
	size_t		new_size;
	const char	*ptr;
	size_t		var_len;

	new_size = 1;
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '$')
		{
			expanded_size_ptr_increase(&ptr, &var_len);
			if (expanded_size_create_var(&var_len, env, &ptr, &new_size) == -1)
				return (-1);
			continue ;
		}
		new_size++;
		ptr++;
	}
	return (new_size);
}
