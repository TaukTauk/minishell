/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:47:36 by rick              #+#    #+#             */
/*   Updated: 2025/03/05 13:53:15 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_pipeline(t_data *data, pid_t *pids, int **pipe_fds)
{
	int	i;

	close_pipes(data, pipe_fds);
	i = 0;
	while (i < data->cmd_count)
	{
		handle_execution_status(pids[i], data);
		i++;
	}
	i = 0;
	while (i < data->cmd_count - 1)
	{
		free(pipe_fds[i]);
		i++;
	}
}
