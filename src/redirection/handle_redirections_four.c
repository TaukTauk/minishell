/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_four.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:58 by talin             #+#    #+#             */
/*   Updated: 2025/03/13 12:48:38 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	handle_input_delimeter(t_command *command, t_data *data)
// {
// 	int			status;

// 	status = 0;
// 	if (command->delimeter)
// 	{
// 		if (handle_delimeter_red_field(command, data, &status))
// 			return (1);
// 	}
// 	if (!status && command->infile)
// 	{
// 		if (handle_input_red_field(command, data))
// 			return (1);
// 	}
// 	return (0);
// }

// int	handle_redirections(t_command *command, t_data *data)
// {
// 	if (!command)
// 		return (1);
// 	if (command->delimeter || command->infile)
// 	{
// 		if (handle_input_delimeter(command, data))
// 			return (1);
// 	}
// 	if (command->outfile || command->outfileappend)
// 	{
// 		if (setup_output_redirection(data, command))
// 		{
// 			cleanup_redirections(command);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// void	cleanup_redirections(t_command *command)
// {
// 	if (!command)
// 		return ;
// 	if ((command->infile) && command->fd_in != -1)
// 	{
// 		close(command->fd_in);
// 		command->fd_in = -1;
// 	}
// 	if ((command->outfile || command->outfileappend) && command->fd_out != -1)
// 	{
// 		close(command->fd_out);
// 		command->fd_out = -1;
// 	}
// }

int	check_input_file_access(char *filename, t_data *data)
{
	if (access(filename, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		data->status = 1;
		return (1);
	}
	if (access(filename, R_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		data->status = 1;
		return (1);
	}
	return (0);
}

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

int	handle_input_file(t_redirection *redir, t_command *command, t_data *data)
{
	int	fd;

	if (check_input_file_access(redir->file_name, data))
		return (1);
	fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
		return (1);
	if (command->fd_in != -1)
		close(command->fd_in);
	command->fd_in = fd;
	if (dup2(command->fd_in, STDIN_FILENO) == -1)
		return (close(command->fd_in), 1);
	return (0);
}

int	handle_heredoc(t_redirection *redir, t_command *command, t_data *data)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_error("minishell: pipe failed"), 1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), 1);
	if (pid == 0)
	{
		close(fd[0]);
		ft_putstr_fd(redir->content, fd[1]);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		if (command->fd_in != -1)
			close(command->fd_in);
		command->fd_in = fd[0];
		if (dup2(command->fd_in, STDIN_FILENO) == -1)
			return (close(command->fd_in), 1);
		update_exit_status(pid, fd, data);
		return (0);
	}
	return (0);
}

int	handle_output_redirection(t_redirection *redir, t_command *command, t_data *data)
{
	int	flags;
	int	fd;

	if (redir->type == REDIRECT_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
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
