/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:44:06 by rick              #+#    #+#             */
/*   Updated: 2025/03/05 13:53:48 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_delimeter(t_command *command, t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		fd_stdin;

	if (!command || !command->delimeter)
		return (1);
	if (pipe(fd) == -1)
		return (ft_error("minishell: pipe failed"), 1);
	pid = fork();
	if (pid == -1)
		return (close_err(fd[0], fd[1]), 1);
	if (pid == 0)
		write_pipe(fd, command);
	else
	{
		close(fd[1]);
		fd_stdin = dup(STDIN_FILENO);
		if (fd_stdin == -1)
			return (close(fd[0]), 1);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (close_both(fd[0], fd_stdin), 1);
		update_exit_status(pid, fd, data);
		return (0);
	}
	return (0);
}

int	ft_input_access(t_io_file *input, t_data *data, int *fd)
{
	if (access(input->file_name, F_OK) != 0)
		return (print_err_nofile(input->file_name, data), 1);
	*fd = open(input->file_name, O_RDONLY);
	if (*fd == -1)
		return (print_err_nofile(input->file_name, data), 1);
	return (0);
}

int	setup_input_redirection(t_command *command, t_data *data)
{
	int				fd;
	t_io_file		*input;

	if (!command || !command->infile)
		return (1);
	input = command->infile;
	while (input)
	{
		if (input->order_value == command->input_order)
		{
			if (input)
			{
				if (ft_input_access(input, data, &fd))
					return (1);
				if (command->fd_in != -1)
					close(command->fd_in);
				command->fd_in = fd;
			}
			if (dup2(command->fd_in, STDIN_FILENO) == -1)
				return (close(command->fd_in), 1);
			return (0);
		}
		input = input->next;
	}
	return (1);
}
