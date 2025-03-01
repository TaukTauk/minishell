/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:22:58 by talin             #+#    #+#             */
/*   Updated: 2025/02/28 19:40:11 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int execute_command(t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!data || !data->commands || !data->commands->args || !data->commands->args[0])
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		if (saved_stdin != -1)
			close(saved_stdin);
		data->status = 1;
		return (0);
	}
	if (handle_redirections(data->commands, data))
		return (restore_std_fds(saved_stdin, saved_stdout), 0);
	if (data->commands->builtin)
		execute_builtin(data->commands, data);
	else
		execve_cmd(data->commands->cmd, data->commands->args, data->env, data);
	restore_std_fds(saved_stdin, saved_stdout);
	cleanup_redirections(data->commands);
	return (1);
}

int	execute_commands(t_data *data)
{
	int		**pipe_fds;
	pid_t	*pids;
	int		i;

	i = 0;
	if (!data || data->cmd_count == 0)
		return (0);
	if (data->cmd_count == 1)
		return (execute_command(data));
	pipe_fds = malloc(sizeof(int *) * (data->cmd_count - 1));
	while (i < data->cmd_count - 1)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		i++;
	}
	pids = malloc(sizeof(pid_t) * data->cmd_count);
	setup_pipes(data, pipe_fds);
	create_pipeline_processes(data, pids, pipe_fds);
	cleanup_pipeline(data, pids, pipe_fds);
	free(pipe_fds);
	free(pids);
	return (1);
}
