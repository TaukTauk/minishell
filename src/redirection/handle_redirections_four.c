/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_four.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:58 by talin             #+#    #+#             */
/*   Updated: 2025/03/19 13:43:39 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_redirection(t_redirection *redir)
{
	if (redir->file_name)
	{
		free(redir->file_name);
		redir->file_name = NULL;
	}
	if (redir->content)
	{
		free(redir->content);
		redir->content = NULL;
	}
}

void	cleanup_redirections(t_command *command)
{
	if (command->fd_in != -1 && command->fd_in != STDIN_FILENO)
	{
		close(command->fd_in);
		command->fd_in = -1;
	}
	if (command->fd_out != -1 && command->fd_out != STDOUT_FILENO)
	{
		close(command->fd_out);
		command->fd_out = -1;
	}
}

static int	check_handle_redirection(t_redirection *current,
	int current_order, t_command *command, t_data *data)
{
	int	result;

	result = 0;
	if (current->order_value == current_order)
	{
		if (current->type == REDIRECT_INPUT)
			result = handle_input_file(current, command, data);
		else if (current->type == REDIRECT_HEREDOC)
			result = handle_heredoc(current, command, data);
		else if (current->type == REDIRECT_OUTPUT
			|| current->type == REDIRECT_APPEND)
			result = handle_output_redirection(current, command, data);
		if (result)
		{
			cleanup_redirections(command);
			return (1);
		}
		return (0);
	}
	return (-1);
}

static int	handling_redirection_support(t_redirection *current,
	int current_order, t_command *command, t_data *data)
{
	int	check;

	while (current)
	{
		check = check_handle_redirection(current,
				current_order, command, data);
		if (check == 0)
			break ;
		else if (check == 1)
			return (1);
		current = current->next;
	}
	return (0);
}

int	handle_redirections(t_command *command, t_data *data)
{
	t_redirection	*current;
	int				current_order;
	int				max_order;

	if (!command || !command->redirections)
		return (0);
	current_order = 1;
	current = NULL;
	max_order = command->red_order;
	while (current_order <= max_order)
	{
		current = command->redirections;
		if (handling_redirection_support(current,
				current_order, command, data) == 1)
			return (1);
		current_order++;
	}
	return (0);
}
