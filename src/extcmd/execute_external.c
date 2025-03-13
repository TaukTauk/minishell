/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:37:48 by rick              #+#    #+#             */
/*   Updated: 2025/03/13 14:58:40 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_getenv(char *name, char **envp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		str = ft_substr(envp[i], 0, j);
		if (ft_strcmp(str, name) == 0)
		{
			free(str);
			return (envp[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}

int	ft_check_set_unset(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0 && envp[i][4] == '=')
			return (1);
	}
	return (0);
}

void	free_command_lexer_in_exec(t_data *data)
{
	int	i;

	i = 0;
	if (data->lexer)
	{
		if (data->lexer->tokens)
		{
			while (data->lexer->tokens[i])
			{
				if (data->lexer->tokens[i])
					free(data->lexer->tokens[i]);
				i++;
			}
			free(data->lexer->tokens);
		}
	}
	if (data->commands)
	{
		free_command(data->commands);
	}
}

void	exec_err_exit(t_command *command, char *cmd_path, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command->args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (cmd_path)
		free(cmd_path);
	free_command_lexer_in_exec(data);
	data -> status = 1;
	exit(errno);
}

int	ft_check_exec_access(char *path)
{
	if (path)
	{
		if (access(path, X_OK) == 0)
			return (1);
		free(path);
		return (0);
	}
	return (0);
}

void	execve_cmd(char *cmd, char **s_cmd, char **envp, t_data *data)
{
	char	*path;
	pid_t	pid;

	if (!cmd)
		return ;
	path = ft_get_path(cmd, envp, -1, data);
	if (!path)
		return (handle_execution_error(data->commands, data, NULL, 1));
	pid = fork();
	if (pid == -1)
	{
		 free(path);
        ft_putstr_fd("minishell: fork: ", STDERR_FILENO);
        ft_putstr_fd(strerror(errno), STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        data->status = 1;
		return ;
	}
	if (pid == 0)
	{
		if (execve(path, s_cmd, envp) == -1)
		{
            if (errno == ENOENT)
            {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                ft_putstr_fd(cmd, STDERR_FILENO);
                ft_putstr_fd(": command not found\n", STDERR_FILENO);
                data->status = 127;
            }
            else if (errno == EACCES)
            {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                ft_putstr_fd(cmd, STDERR_FILENO);
                ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
                data->status = 126;
            }
            else
            {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                ft_putstr_fd(cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                ft_putstr_fd(strerror(errno), STDERR_FILENO);
                ft_putstr_fd("\n", STDERR_FILENO);
                data->status = 1;
            }
			if (path)
            	free(path);
            free_command_lexer_in_exec(data);
            exit(data->status);
        }
	}
	else
	{
		handle_execution_status(pid, data);
		if (path)
			free(path);
	}
}
