/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:46:50 by rick              #+#    #+#             */
/*   Updated: 2025/02/28 09:49:08 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_execution_status(pid_t pid, t_data *data)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->status = 128 + WTERMSIG(status);
	if (status > 128)
		status = status - 128;
}

void	update_exit_status(pid_t pid, int fd[2], t_data *data)
{
	int		status;

	waitpid(pid, &status, 0);
	close(fd[0]);
	if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->status = 128 + WTERMSIG(status);
}
