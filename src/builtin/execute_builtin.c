/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:36:35 by rick              #+#    #+#             */
/*   Updated: 2025/03/15 20:11:57 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_command *command, t_data *data)
{
	t_envp	*current;

	if (command->args[1])
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putstr_fd(command->args[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		data->status = 127;
		return ;
	}
	current = data->envp;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	data->status = 0;
}

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf != NULL)
	{
		ft_putstr_fd(buf, 1);
		write(1, "\n", 1);
		free(buf);
	}
	else
		perror("getcwd");
}

int	execute_builtin(t_command *commands, t_data *data)
{
	if (ft_strcmp(commands->cmd, "env") == 0)
		return (ft_env(commands, data), 1);
	else if (ft_strcmp(commands->cmd, "echo") == 0)
		return (ft_echo(commands, data), 1);
	else if (ft_strcmp(commands->cmd, "cd") == 0)
		return (ft_cd(commands, data), 1);
	else if (ft_strcmp(commands->cmd, "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(commands->cmd, "export") == 0)
		return (ft_export(commands, data), 1);
	else if (ft_strcmp(commands->cmd, "unset") == 0)
		return (ft_unset(commands, data), 1);
	else if (ft_strcmp(commands->cmd, "exit") == 0)
		return (ft_exit(commands, data), 1);
	return (1);
}
