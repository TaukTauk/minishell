/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:44:06 by rick              #+#    #+#             */
/*   Updated: 2025/03/13 13:00:45 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_input_file_access(char *filename, t_data *data)
{
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

	if (check_input_file_access(redir->file_name, data))
		return (1);
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

int	handle_heredoc(t_redirection *redir, t_command *command, t_data *data)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_error("minishell: pipe failed"), 1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), 1);
	if (pid == 0)
	{
		close(fd[0]);
		ft_putstr_fd(redir->content, fd[1]);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		if (command->fd_in != -1)
			close(command->fd_in);
		command->fd_in = fd[0];
		if (dup2(command->fd_in, STDIN_FILENO) == -1)
			return (close(command->fd_in), 1);
		update_exit_status(pid, fd, data);
		return (0);
	}
	return (0);
}
