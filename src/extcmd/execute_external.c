/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:37:48 by rick              #+#    #+#             */
/*   Updated: 2025/03/17 11:08:36 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_err_exit(t_command *command, char *cmd_path, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command->args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (cmd_path)
		free(cmd_path);
	free_command_lexer_in_exec(data);
	data -> status = 1;
	exit(errno);
}

static void	remaining_error(t_data *data, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->status = 1;
}

static void	handle_pid_zero(t_data *data, char *cmd, char **path)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		data->status = 127;
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		data->status = 126;
	}
	else
		remaining_error(data, cmd);
	if (*path)
		free(*path);
	exit(data->status);
}

static void	pid_error(char **path, t_data *data)
{
	free(*path);
	ft_putstr_fd("minishell: fork: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->status = 1;
	return ;
}

void	execve_cmd(char *cmd, char **s_cmd, char **envp, t_data *data)
{
	char	*path;
	pid_t	pid;

	if (!cmd)
		return ;
	path = ft_get_path(cmd, envp, -1, data);
	if (!path)
		return (handle_execution_error(data->commands, data, NULL, 1));
	pid = fork();
	if (pid == -1)
		pid_error(&path, data);
	if (pid == 0)
	{
		if (execve(path, s_cmd, envp) == -1)
			handle_pid_zero(data, cmd, &path);
	}
	else
	{
		handle_execution_status(pid, data);
		if (path)
			free(path);
	}
}
