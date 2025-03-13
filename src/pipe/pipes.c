/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:45:08 by rick              #+#    #+#             */
/*   Updated: 2025/03/13 11:27:53 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_up_pipes(t_data *data, int **pipe_fds)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			ft_putstr_fd("minishell: pipe creation failed\n", 2);
			exit(1);
		}
		i++;
	}
}

void	close_pipes(t_data *data, int **pipe_fds)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}

void	setup_child_pipes(t_data *data, int **pipe_fds, int i)
{
	if (i > 0)
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		close(pipe_fds[i - 1][1]);
	}
	if (i < data->cmd_count - 1)
	{
		dup2(pipe_fds[i][1], STDOUT_FILENO);
		close(pipe_fds[i][0]);
	}
}

void	run_piped_command(t_data *data, int **pipe_fds, int i)
{
	t_command	*cmd;
	int			j;

	setup_child_pipes(data, pipe_fds, i);
	close_pipes(data, pipe_fds);
	cmd = data->commands;
	j = 0;
	while (cmd)
	{
		if (j == i)
			execute_piped_command(cmd, data);
		cmd = cmd->next;
		j++;
	}
}

void	create_pipelines(t_data *data, pid_t *pids, int **pipe_fds)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ft_putstr_fd("minishell: fork failed\n", 2);
			break ;
		}
		if (pids[i] == 0)
			run_piped_command(data, pipe_fds, i);
		i++;
	}
}
