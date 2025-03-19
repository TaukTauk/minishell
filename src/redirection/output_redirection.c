/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:48:02 by rick              #+#    #+#             */
/*   Updated: 2025/03/19 20:38:09 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_output_redir(t_data *data, char *name)
{
	data->status = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
}

int	handle_output_redirection(t_redirection *redir,
	t_command *command, t_data *data)
{
	int	flags;
	int	fd;

	if (redir->type == REDIRECT_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (redir->error == 1)
		return (error_output_redir(data, redir->file_name), 1);
	fd = open(redir->file_name, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file_name, STDERR_FILENO);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		data->status = 1;
		return (1);
	}
	if (command->fd_out != STDOUT_FILENO)
		close(command->fd_out);
	command->fd_out = fd;
	if (dup2(command->fd_out, STDOUT_FILENO) == -1)
		return (close(command->fd_out), 1);
	return (0);
}
