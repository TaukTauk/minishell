/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:51:07 by rick              #+#    #+#             */
/*   Updated: 2025/03/13 11:48:39 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_both(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

void	write_pipe(int fd[2], t_command *command)
{
	size_t			len;
	ssize_t			written;
	t_redirection	*current;

	current = command->redirections;
	while (current)
	{
		if (current->order_value == command->input_order)
		{
			close(fd[0]);
			len = ft_strlen(current->content);
			written = write(fd[1], current->content, len);
			write(fd[1], "\n", 1);
			close(fd[1]);
			if (written == -1)
				exit(1);
			exit(0);
		}
		current = current->next;
	}
}

void	execute_in_child(char *cmd_path, t_command *command, t_data *data)
{
	if (handle_redirections(command, data))
	{
		free(cmd_path);
		exit(1);
	}
	if (execve(cmd_path, command->args, data->env) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command->args[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		data->status = 1;
		free(cmd_path);
		exit(errno);
	}
}

void	execute_piped_command(t_command *command, t_data *data)
{
	char	*cmd_path;

	if (handle_redirections(command, data) != 0)
		exit (1);
	if (command->builtin)
	{
		execute_builtin(command, data);
		exit(data->status);
	}
	if (!command->args || !command->args[0])
		return ;
	cmd_path = ft_get_path(command->args[0], data->env, -1);
	if (!cmd_path || !ft_check_exec_access(cmd_path))
	{
		handle_execution_error(command, data, NULL, 1);
		exit(127);
	}
	execute_in_child(cmd_path, command, data);
}
