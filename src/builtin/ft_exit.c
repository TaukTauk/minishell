/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:47:44 by talin             #+#    #+#             */
/*   Updated: 2025/03/20 16:57:25 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	free_data(data);
	return (num % 256);
}

static void	close_fds_all(int *fd_in, int *fd_out, t_command *command)
{
	restore_std_fds(fd_in, fd_out);
	cleanup_redirections(command);
}

int	ft_exit(t_command *command, t_data *data, int *fd_in, int *fd_out)
{
	int	fd;

	close_fds_all(fd_in, fd_out, command);
	fd = dup(STDOUT_FILENO);
	if (isatty(fd))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	close(fd);
	if (!command->args[1])
	{
		free_data(data);
		exit(data->status);
	}
	if (!exit_valid_argument(command->args[1]))
	{
		error_numeric(command->args[1], data);
		free_data(data);
		exit(2);
	}
	if (command->args[2])
	{
		error_args(command->args[0], data);
		free_data(data);
		exit(1);
	}
	exit(exit_status(command->args[1], data));
}

int	ft_exit_pipe(t_command *command, t_data *data)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (isatty(fd))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	close(fd);
	if (!command->args[1])
	{
		free_data(data);
		exit(data->status);
	}
	if (!exit_valid_argument(command->args[1]))
	{
		error_numeric(command->args[1], data);
		free_data(data);
		exit(2);
	}
	if (command->args[2])
	{
		error_args(command->args[0], data);
		free_data(data);
		exit(1);
	}
	exit(exit_status(command->args[1], data));
}
