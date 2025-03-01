/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:44:06 by rick              #+#    #+#             */
/*   Updated: 2025/02/28 17:09:07 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	setup_delimeter(t_command *command, t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		saved_stdin;

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
		saved_stdin = dup(STDIN_FILENO);
		if (saved_stdin == -1)
			return (close(fd[0]), 1);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (close_both(fd[0], saved_stdin), 1);
		update_exit_status(pid, fd, data);
		return (0);
	}
	return (0);
}

int	setup_input_redirection(t_command *command, t_data *data)
{
	int				fd;
	t_io_file	*input;

	if (command->delimeter)
		return (setup_delimeter(command, data));
	input = command->infile;
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

int	setup_output_redirection(t_data *data, t_command *command)
{
	int				fd;
	int				flags;
	t_io_file	*last_output;

	if (!command->outfile)
		return (0);
	if (command->outfile->redirect_type == REDIRECT_APPEND)
	{
		last_output = command->outfile;
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
	command->fd_out = fd;
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), 1);
	return (0);
}