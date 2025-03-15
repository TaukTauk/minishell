/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:32:25 by talin             #+#    #+#             */
/*   Updated: 2025/03/14 22:29:59 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	calculate_expanded_size(const char *input, t_data *data)
{
	size_t		new_size;
	const char	*ptr;
	size_t		var_len;
	int			inside_single_quote;
    
	inside_single_quote = 0;
	new_size = 0;
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '\'')
			inside_single_quote = !inside_single_quote;
		if (*ptr == '$' && !inside_single_quote)
		{
			ptr++;
			if (!*ptr)
			{
				new_size++;
				break ;
			}
			if (*ptr == '$')
			{
				char *pid_str = ft_itoa(getpid());
				if (pid_str)
				{
					new_size += ft_strlen(pid_str);
					free(pid_str);
				}
				ptr++;
				continue;
			}
			var_len = 0;
			while (*ptr && ft_is_valid_name_character(*ptr))
			{
				var_len++;
				ptr++;
			}
			if (var_len == 0)
			{
				new_size++;
				continue;
			}
			char *var_name = ft_strndup(ptr - var_len, var_len);
			if (!var_name)
				return (-1); 
			if (var_name[0] == '?')
			{
				char *status_str = ft_itoa(data->status);
 				if (status_str)
				{
					new_size += ft_strlen(status_str);
					free(status_str);
				}
				if (var_name[1])
					new_size += ft_strlen(var_name) - 1;
				free(var_name);
				continue ;
			}
			char *var_value = get_env_value(data->env, var_name);
			if (var_value)
				new_size += ft_strlen(var_value);
			free(var_name);
			continue ;
		}
		new_size++;
		ptr++;
	}
	return (new_size + 1);
}

void ft_quote_handle(char **ptr, int *inside_single_quote,
            int *inside_double_quote)
{
    if (**ptr == '\'' && !(*inside_double_quote))
        *inside_single_quote = !(*inside_single_quote);
    if (**ptr == '\"' && !(*inside_single_quote))
        *inside_double_quote = !(*inside_double_quote);
}

void expand_variable_copy(char **ptr, t_data *data, char **output_ptr)
{
    int inside_single_quote;
    int inside_double_quote;

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
                break;
            continue;
        }
        if (**ptr)
            *(*output_ptr)++ = *(*ptr)++;
    }
    *(*output_ptr) = '\0';
}

char *expand_variable(char *input, t_data *data)
{
    char    *expanded_str;
    char    *ptr;
    char    *output_ptr;
    int     size;

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

// static void	expanded_size_ptr_increase(const char **ptr, size_t *var_len)
// {
// 	(*ptr)++;
// 	(*var_len) = 0;
// 	while (ft_is_valid_name_character(**ptr))
// 	{
// 		(*var_len)++;
// 		(*ptr)++;
// 	}
// }

// static int	expanded_size_create_var(size_t *var_len, t_data *data,
// 				const char **ptr, size_t *new_size)
// {
// 	char	*var_name;
// 	char	*var_value;

// 	if ((*var_len) > 0)
// 	{
// 		var_name = ft_strndup((*ptr) - (*var_len), (*var_len));
// 		if (!var_name)
// 			return (-1);
// 		if (!ft_strcmp(var_name, "?"))
// 		{
// 			var_value = ft_itoa(data->status);
// 			free(var_name);
// 			if (var_value)
// 			{
// 				(*new_size) += ft_strlen(var_value);
// 				free(var_value);
// 			}
// 			return (0);
// 		}
// 		var_value = get_env_value(data->env, var_name);
// 		free(var_name);
// 		if (var_value)
// 			(*new_size) += ft_strlen(var_value);
// 	}
// 	return (0);
// }

// size_t	calculate_expanded_size(const char *input, t_data *data)
// {
// 	size_t		new_size;
// 	const char	*ptr;
// 	size_t		var_len;

// 	new_size = 1;
// 	ptr = input;
// 	while (*ptr)
// 	{
// 		if (*ptr == '$')
// 		{
// 			expanded_size_ptr_increase(&ptr, &var_len);
// 			if (expanded_size_create_var(&var_len, data, &ptr, &new_size) == -1)
// 				return (-1);
// 			continue ;
// 		}
// 		new_size++;
// 		ptr++;
// 	}
// 	return (new_size);
// }
