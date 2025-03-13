/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_four.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:58 by talin             #+#    #+#             */
/*   Updated: 2025/03/13 13:00:34 by talin            ###   ########.fr       */
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

int	handle_redirections(t_command *command, t_data *data)
{
	t_redirection	*current = NULL;
	int				current_order = 1;
	int				max_order = 0;
    
	if (!command || !command->redirections)
		return (0);
	max_order = command->red_order;
	while (current_order <= max_order)
	{
		current = command->redirections;
		while (current)
		{
			if (current->order_value == current_order)
			{
				int result = 0;
				if (current->type == REDIRECT_INPUT)
				{
					result = handle_input_file(current, command, data);
				}
				else if (current->type == REDIRECT_HEREDOC)
				{
					result = handle_heredoc(current, command, data);
				}
				else if (current->type == REDIRECT_OUTPUT || current->type == REDIRECT_APPEND)
				{
					result = handle_output_redirection(current, command, data);
				}
				if (result)
				{
					cleanup_redirections(command);
					return (1);
				}
				break ;
			}
			current = current->next;
		}
		current_order++;
	}
	return (0);
}
