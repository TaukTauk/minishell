/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:44:06 by rick              #+#    #+#             */
/*   Updated: 2025/03/19 21:34:41 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_input_file_access(char *filename, t_data *data, t_redirection *redir)
{
	if (redir->error == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		data->status = 1;
		return (1);
	}
	if (access(filename, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		data->status = 1;
		return (1);
	}
	if (access(filename, R_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		data->status = 1;
		return (1);
	}
	return (0);
}

int	handle_input_file(t_redirection *redir, t_command *command, t_data *data)
{
	int	fd;

	if (check_input_file_access(redir->file_name, data, redir))
		return (1);
	if (redir->order_value != command->input_order)
		return (0);
	fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
		return (1);
	if (command->fd_in != -1)
		close(command->fd_in);
	command->fd_in = fd;
	if (dup2(command->fd_in, STDIN_FILENO) == -1)
		return (close(command->fd_in), 1);
	return (0);
}

static void	pid_zero_exit(int *fd, t_redirection *redir)
{
	size_t	len;
	ssize_t	written;

	close(fd[0]);
	len = ft_strlen(redir->content);
	written = write(fd[1], redir->content, len);
	close(fd[1]);
	if (written == -1)
		exit(1);
	exit(0);
}

int	handle_heredoc(t_redirection *redir, t_command *command, t_data *data)
{
	int		fd[2];
	int		std_in;
	pid_t	pid;

	if (redir->order_value != command->input_order)
		return (0);
	if (pipe(fd) == -1)
		return (ft_error("minishell: pipe failed"), 1);
	pid = fork();
	if (pid == -1)
		return (close_err(fd[0], fd[1]), 1);
	if (pid == 0)
		pid_zero_exit(fd, redir);
	else
	{
		close(fd[1]);
		std_in = dup(STDIN_FILENO);
		if (std_in == -1)
			return (close(fd[0]), 1);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (close_both(fd[0], std_in), 1);
		update_exit_status(pid, fd, data);
		return (0);
	}
	return (0);
}
