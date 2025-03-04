/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:47:44 by talin             #+#    #+#             */
/*   Updated: 2025/03/04 12:30:20 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exit_valid_argument(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	exit_overflow(char *string, int *i, t_data *data)
{
	long long	number;
	int			length;

	length = 0;
	while (string[*i + length] && ft_isdigit(string[*i + length]))
		length++;
	if (length > 19)
	{
		error_numeric(string, data);
		exit(2);
	}
	number = 0;
	while (string[*i] && ft_isdigit(string[*i]))
	{
		if (number > (LLONG_MAX - (string[*i] - '0')) / 10)
		{
			error_numeric(string, data);
			exit(2);
		}
		number = number * 10 + (string[*i] - '0');
		(*i)++;
	}
	return (number);
}

static unsigned char	exit_status(char *str, t_data *data)
{
	long long	num;
	int			i;
	int			sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	num = exit_overflow(str, &i, data);
	num *= sign;
	return (num % 256);
}

int	ft_exit(t_command *command, t_data *data)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (isatty(fd))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!command->args[1])
	{
		exit(data->status);
	}
	if (!exit_valid_argument(command->args[1]))
	{
		error_numeric(command->args[1], data);
		exit(2);
	}
	if (command->args[2])
	{
		error_args(command->args[0], data);
		exit(1);
	}
	exit(exit_status(command->args[1], data));
}
