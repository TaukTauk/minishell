/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:42:16 by rick              #+#    #+#             */
/*   Updated: 2025/02/28 10:24:40 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_execution_error(t_command *command, t_data *data, char *cmd_path, int error_type)
{
	if (error_type == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		data->status = 127;
	}
	else if (error_type == 2)
	{
		ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
		data->status = 1;
	}
	free(cmd_path);
}

void	ft_error(const char *message)
{
	ft_putstr_fd((char *)message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	close_err(int fd1, int fd2)
{
	close_both(fd1, fd2);
	ft_error("minishell: fork failed");
}

void	print_err_nofile(char *filename, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->status = 1;
}