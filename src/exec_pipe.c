/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:51:07 by rick              #+#    #+#             */
/*   Updated: 2025/02/28 10:39:09 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_both(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

void	write_pipe(int fd[2], t_command *command)
{
	size_t	len;
	ssize_t	written;

	close(fd[0]);
	len = ft_strlen(command->delimeter->content);
	written = write(fd[1], command->delimeter->content, len);
	write(fd[1], "\n", 1);
	close(fd[1]);
	if (written == -1)
		exit(1);
	exit(0);
}

void	execute_in_child(char *cmd_path, t_command *command, t_data *data)
{
	if (handle_redirections(command, data))
	{
		free(cmd_path);
		exit(1);
	}
	if (execve(cmd_path, command->args, data->env) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command->args[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		data->status = 1;
		free(cmd_path);
		exit(errno);
	}
}

void	execute_piped_command(t_command *command, t_data *data)
{
	char	*cmd_path;

	if (handle_redirections(command, data) != 0)
		exit (1);
	if (command->builtin)
	{
		execute_builtin(command, data);
		exit(data->status);
	}
	cmd_path = ft_get_path(command->args[0], data->env, -1);
	if (!cmd_path)
	{
		handle_execution_error(command, data, NULL, 1);
		exit(127);
	}
	execute_in_child(cmd_path, command, data);
}
