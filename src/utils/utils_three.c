/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:48:03 by rick              #+#    #+#             */
/*   Updated: 2025/03/19 23:00:25 by rick             ###   ########.fr       */
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
