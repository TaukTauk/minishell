/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:48:03 by rick              #+#    #+#             */
/*   Updated: 2025/03/21 13:36:28 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_str_copy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	if (!src)
		return ;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_error_in_red_two(t_data *data, t_command **command_list)
{
	data->status = 2;
	ft_putendl_fd("minishell: malloc for input redirection file", 2);
	free_commands(*command_list);
}

void	error_out_red_two(t_data *data, t_command **command_list)
{
	data->status = 2;
	ft_putendl_fd("minishell: malloc for output redirection file", 2);
	free_commands(*command_list);
}

int	empty_directory(char *dest_path)
{
	if (ft_strlen(dest_path) <= 0)
		return (1);
	return (0);
}

void	ft_quote_handle_size(const char *ptr, int *inside_single_quote,
		int *inside_double_quote)
{
	if (*ptr == '\'' && !(*inside_double_quote))
		*inside_single_quote = !(*inside_single_quote);
	if (*ptr == '\"' && !(*inside_single_quote))
		*inside_double_quote = !(*inside_double_quote);
}
