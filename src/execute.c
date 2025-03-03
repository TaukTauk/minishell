/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:22:58 by talin             #+#    #+#             */
/*   Updated: 2025/03/03 21:15:16 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_std_fds(int fd_stdin, int fd_stdout)
{
	dup2(fd_stdin, STDIN_FILENO);
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd_stdin);
	close(fd_stdout);
}

int execute_command(t_data *data)
{
	int	fd_stdin;
	int	fd_stdout;

	if (!data || !data->commands || !data->commands->args || !data->commands->args[0])
		return (0);
	fd_stdin = dup(STDIN_FILENO);
	fd_stdout = dup(STDOUT_FILENO);
	if (fd_stdin == -1 || fd_stdout == -1)
	{
		if (fd_stdin != -1)
			close(fd_stdin);
		data->status = 1;
		return (0);
	}
	if (handle_redirections(data->commands, data))
		return (restore_std_fds(fd_stdin, fd_stdout), 0);
	if (data->commands->builtin)
		execute_builtin(data->commands, data);
	else
		execve_cmd(data->commands->cmd, data->commands->args, data->env, data);
	restore_std_fds(fd_stdin, fd_stdout);
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
