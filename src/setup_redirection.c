/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:44:06 by rick              #+#    #+#             */
/*   Updated: 2025/03/02 15:44:12 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (pid == 0) {
		write_pipe(fd, command);
	}
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

int	setup_input_redirection(t_command *command, t_data *data)
{
	int				fd;
	t_io_file	*input;

	if (!command || !command->infile)
		return (1);
	input = command->infile;
	while (input)
	{
		if (input->order_value == command->input_order)
		{
			if (input)
			{
				if (access(input->file_name, F_OK) != 0)
					return (print_err_nofile(input->file_name, data), 1);
				fd = open(input->file_name, O_RDONLY);
				if (fd == -1)
					return (print_err_nofile(input->file_name, data), 1);
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

int	setup_output_redirection(t_data *data, t_command *command)
{
	int			fd;
	int			flags;
	t_io_file	*last_output;
	t_io_file	*current;
	int			status;

	if (!command->outfile && !command->outfileappend)
		return (0);
	status = 0;
	if (command->outfileappend)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		current = command->outfileappend;
		while (current)
		{
			fd = open(current->file_name, flags, 0644);
			if (fd == -1)
				return (print_err_nofile(current->file_name, data), 1);
			if (current->order_value == command->output_order)
			{
				last_output = current;
				status = 1;
				break ;
			}
			else
				close(fd);
			current = current->next;
		}
	}
	if (command->outfile && !status)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		current = command->outfile;
		while (current)
		{
			fd = open(current->file_name, flags, 0644);
			if (fd == -1)
				return (print_err_nofile(current->file_name, data), 1);
			if (current->order_value == command->output_order)
			{
				last_output = current;
				status = 1;
				break ;
			}
			else
				close(fd);
			current = current->next;
		}
	}
	if (!status)
	{
		if (command->outfileappend)
		{
			last_output = command->outfileappend;
			flags = O_WRONLY | O_CREAT | O_APPEND;
		}
		else
		{
			last_output = command->outfile;
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		}
		fd = open(last_output->file_name, flags, 0644);
		if (fd == -1)
			return (print_err_nofile(last_output->file_name, data), 1);
	}
	command->fd_out = fd;
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), 1);
	return (0);
}
