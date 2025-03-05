/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:48:02 by rick              #+#    #+#             */
/*   Updated: 2025/03/05 13:53:44 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	outfileappend_setup(t_command **command, t_data *data, int *status)
{
	int			flags;
	t_io_file	*current;
	int			fd;

	flags = O_WRONLY | O_CREAT | O_APPEND;
	current = (*command)->outfileappend;
	while (current)
	{
		fd = open(current->file_name, flags, 0644);
		if (fd == -1)
			return (print_err_nofile(current->file_name, data), 1);
		if (current->order_value == (*command)->output_order && !(*status))
		{
			*status = 1;
			(*command)->fd_out = fd;
		}
		else
			close(fd);
		current = current->next;
	}
	return (0);
}

static int	outfile_setup(t_command **command, t_data *data, int *status)
{
	int			flags;
	t_io_file	*current;
	int			fd;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	current = (*command)->outfile;
	while (current)
	{
		fd = open(current->file_name, flags, 0644);
		if (fd == -1)
			return (print_err_nofile(current->file_name, data), 1);
		if (current->order_value == (*command)->output_order && !(*status))
		{
			*status = 1;
			(*command)->fd_out = fd;
		}
		else
			close(fd);
		current = current->next;
	}
	return (0);
}

static int	setup_output_red(t_command **command, t_data *data)
{
	int			fd;
	int			flags;
	t_io_file	*last_output;

	if ((*command)->outfileappend)
	{
		last_output = (*command)->outfileappend;
		flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	else
	{
		last_output = (*command)->outfile;
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	}
	fd = open(last_output->file_name, flags, 0644);
	if (fd == -1)
		return (print_err_nofile(last_output->file_name, data), 1);
	(*command)->fd_out = fd;
	return (0);
}

int	setup_output_redirection(t_data *data, t_command *command)
{
	int			status;

	if (!command->outfile && !command->outfileappend)
		return (0);
	status = 0;
	if (command->outfileappend)
	{
		if (outfileappend_setup(&command, data, &status))
			return (1);
	}
	if (command->outfile)
	{
		if (outfile_setup(&command, data, &status))
			return (1);
	}
	if (!status)
	{
		if (setup_output_red(&command, data))
			return (1);
	}
	if (dup2(command->fd_out, STDOUT_FILENO) == -1)
		return (close(command->fd_out), 1);
	return (0);
}
