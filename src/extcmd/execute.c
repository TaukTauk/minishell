/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:22:58 by talin             #+#    #+#             */
/*   Updated: 2025/03/20 21:32:20 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	restore_std_fds(int *stdin_fd, int *stdout_fd)
{
	if (dup2(*stdin_fd, STDIN_FILENO) == -1)
		perror("Failed to restore stdin");
	if (*stdin_fd != -1)
		close(*stdin_fd);
	*stdin_fd = -1;
	if (dup2(*stdout_fd, STDOUT_FILENO) == -1)
		perror("Failed to restore stdout");
	if (*stdout_fd != -1)
		close(*stdout_fd);
	*stdout_fd = -1;
}

static int	std_util(int *fd_stdin, int *fd_stdout, t_data *data)
{
	*fd_stdin = dup(STDIN_FILENO);
	*fd_stdout = dup(STDOUT_FILENO);
	if (*fd_stdin == -1 || *fd_stdout == -1)
	{
		if (*fd_stdin != -1)
		{
			close(*fd_stdin);
			*fd_stdin = -1;
		}
		if (*fd_stdout != -1)
		{
			close(*fd_stdout);
			*fd_stdin = -1;
		}
		data->status = 1;
		return (-1);
	}
	return (1);
}

int	execute_command(t_data *data)
{
	int	fd_stdin;
	int	fd_stdout;

	if (!data || !data->commands)
		return (0);
	signal(SIGINT, handle_sigint_two);
	signal(SIGQUIT, handle_sigquit);
	if (std_util(&fd_stdin, &fd_stdout, data) == -1)
		return (0);
	if (handle_redirections(data->commands, data))
	{
		restore_std_fds(&fd_stdin, &fd_stdout);
		return (0);
	}
	if (data->commands->builtin)
		execute_builtin(data->commands, data, &fd_stdin, &fd_stdout);
	else
		execve_cmd(data->commands->cmd, data->commands->args, data->env, data);
	restore_std_fds(&fd_stdin, &fd_stdout);
	cleanup_redirections(data->commands);
	return (1);
}

int	execute_commands(t_data *data)
{
	int		**pipe_fds;
	pid_t	*pids;
	int		i;

	i = -1;
	if (!data || data->cmd_count == 0)
		return (0);
	if (data->cmd_count == 1)
		return (execute_command(data));
	pipe_fds = malloc(sizeof(int *) * (data->cmd_count - 1));
	while (++i < data->cmd_count - 1)
		pipe_fds[i] = malloc(sizeof(int) * 2);
	pids = malloc(sizeof(pid_t) * data->cmd_count);
	set_up_pipes(data, pipe_fds);
	create_pipelines(data, pids, pipe_fds);
	clear_pipeline(data, pids, pipe_fds);
	free(pipe_fds);
	free(pids);
	return (1);
}
