/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_four.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:58 by talin             #+#    #+#             */
/*   Updated: 2025/03/05 13:53:27 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_input_delimeter(t_command *command, t_data *data)
{
	int			status;

	status = 0;
	if (command->delimeter)
	{
		if (handle_input_red_field(command, data, &status))
			return (1);
	}
	if (!status && command->infile)
	{
		if (handle_delimeter_red_field(command, data))
			return (1);
	}
	return (0);
}

int	handle_redirections(t_command *command, t_data *data)
{
	if (!command)
		return (1);
	if (command->delimeter || command->infile)
	{
		if (handle_input_delimeter(command, data))
			return (1);
	}
	if (command->outfile || command->outfileappend)
	{
		if (setup_output_redirection(data, command))
		{
			cleanup_redirections(command);
			return (1);
		}
	}
	return (0);
}

void	cleanup_redirections(t_command *command)
{
	if (!command)
		return ;
	if ((command->infile) && command->fd_in != -1)
	{
		close(command->fd_in);
		command->fd_in = -1;
	}
	if ((command->outfile || command->outfileappend) && command->fd_out != -1)
	{
		close(command->fd_out);
		command->fd_out = -1;
	}
}
