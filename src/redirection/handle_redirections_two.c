/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:52:57 by rick              #+#    #+#             */
/*   Updated: 2025/03/12 12:33:55 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_sigint_delim(int sig)
{
    (void)sig;
    g_delim_interrupt = 1;
    write(1, "\n", 1);
	printf("control c\n");
    rl_replace_line("", 0);
	rl_on_new_line();
}

int	delimeter_lines(t_io_file *delimeter, t_data *data)
{
	char	*line;
	(void)data;

	while (1)
	{
		signal(SIGINT, handle_sigint_delim);
		if (g_delim_interrupt)
        {
            g_delim_interrupt = 0;
            return (0);
        }
		line = readline("> ");
		if (!line)
		{
			error_delimeter(delimeter->file_name);
			write(1, "\n", 1);
			return (1);
		}
		if (ft_strcmp(line, delimeter->file_name) == 0)
			return (free(line), 1);
		if (!delimeter_append(delimeter, line))
			return (free(line), 0);
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
	if (!delimeter_lines(delimeter, data))
	{
		printf("hello from deli read\n");
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

void	ft_free_infile(t_command *command)
{
	t_io_file	*current;
	t_io_file	*next;

	if (command->infile)
	{
		current = command->infile;
		while (current)
		{
			next = current->next;
			if (current->file_name)
			{
				free(current->file_name);
				current->file_name = NULL;
			}
			if (current->content)
			{
				free(current->content);
				current->content = NULL;
			}
			free(current);
			current = next;
		}
		command->infile = NULL;
	}
}

int	handle_delimeter_red_field(t_command *command, t_data *data, int *status)
{
	t_io_file	*current;

	current = command->delimeter;
	while (current)
	{
		if (current->order_value == command->input_order)
		{
			ft_free_infile(command);
			if (setup_delimeter(command, data))
				return (1);
			*status = 1;
			break ;
		}
		current = current->next;
	}
	return (0);
}

int	handle_input_red_field(t_command *command, t_data *data)
{
	t_io_file	*current;

	current = command->infile;
	while (current)
	{
		if (current->order_value == command->input_order)
		{
			if (setup_input_redirection(command, data))
			{
				cleanup_redirections(command);
				return (1);
			}
			break ;
		}
		current = current->next;
	}
	return (0);
}
