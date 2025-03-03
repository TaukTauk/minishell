/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:55:32 by talin             #+#    #+#             */
/*   Updated: 2025/03/03 09:56:02 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	empty_args(t_data *data)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	data->status = 0;
	return (0);
}

int	valid_option(const char *argument)
{
	int	i;

	if (!argument || argument[0] != '-' || argument[1] != 'n')
		return (0);
	i = 2;
	while (argument[i])
	{
		if (argument[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_option(char **arguments, int *i)
{
	int	new_line;
	int	valid;

	new_line = 0;
	valid = 0;
	while (arguments[*i])
	{
		if (!valid && valid_option(arguments[*i]))
		{
			new_line = 1;
			(*i)++;
		}
		else
		{
			valid = 1;
			break ;
		}
	}
	return (new_line);
}

void	echo_print(char **arguments, int start)
{
	int	i;

	i = start;
	while (arguments[i])
	{
		ft_putstr_fd(arguments[i], STDOUT_FILENO);
		if (arguments[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

int	ft_echo(t_command *command, t_data *data)
{
	int	i;
	int	new_line;

	i = 1;
	if (!command->args[i])
		return (empty_args(data));
	new_line = echo_option(command->args, &i);
	echo_print(command->args, i);
	if (!new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	data->status = 0;
	return (0);
}