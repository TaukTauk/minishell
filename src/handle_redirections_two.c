/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:52:57 by rick              #+#    #+#             */
/*   Updated: 2025/02/28 17:08:53 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	delimeter_lines(t_io_file *delimeter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			error_delimeter(delimeter->file_name);
			write(1, "\n", 1);
			return (1);
		}
		if (ft_strcmp(line, delimeter->file_name) == 0)
		{
			rl_clear_history();
			return (free(line), 1);
		}
		if (!delimeter_append(delimeter, line))
		{
			rl_clear_history();
			return (free(line), 0);
		}
		add_history(line);
		free(line);
	}
}

void	delimeter_expand(t_io_file *delimeter, t_data *data)
{
	char	*expand;

	if (!delimeter || !delimeter->content)
		return ;
	expand = quote_expand(delimeter->content, data);
	if (expand)
	{
		free(delimeter->content);
		delimeter->content = expand;
	}
	else
		ft_error("delimeter: failed to expand delimeter");
}

void	delimeter_read(t_io_file *delimeter, t_command *command, t_data *data)
{
	if (!delimeter || !command || !command->delimeter)
		return ;
	if (!delimeter_content(delimeter))
		return ;
	if (!delimeter_lines(delimeter))
	{
		free(delimeter->content);
		delimeter->content = NULL;
		return ;
	}
	delimeter_expand(delimeter, data);
	if (command->delimeter)
	{
		if (command->delimeter != delimeter)
		{
			free(command->delimeter->content);
			command->delimeter->content = ft_strdup(delimeter->content);
			if (!command->delimeter->content)
			{
				ft_error("delimeter: memory allocation failed");
				return ;
			}
		}
	}
}

int	handle_redirections(t_command *command, t_data *data)
{
	if (!command)
		return (1);
	if (command->delimeter)
	{
		if (setup_delimeter(command, data))
			return (1);
	}
	if (command->infile && !command->delimeter)
	{
		if (setup_input_redirection(command, data))
		{
			cleanup_redirections(command);
			return (1);
		}
	}
	if (command->outfile)
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
	if ((command->outfile) && command->fd_out != -1)
	{
		close(command->fd_out);
		command->fd_out = -1;
	}
}
