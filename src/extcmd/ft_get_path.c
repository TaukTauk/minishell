/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:18:50 by talin             #+#    #+#             */
/*   Updated: 2025/03/17 15:15:27 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	access_error(t_data *data, char **exec)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(*exec, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	data->status = 126;
	free(*exec);
}

static char	*root_directory(t_data *data, char *cmd, char **envp)
{
	int		status;
	char	*exec;

	exec = ft_get_home_path(cmd, envp);
	status = ft_check_file_type(exec);
	if (status == 0)
	{
		ft_error_directory(exec, data, 0);
		free(exec);
		return (NULL);
	}
	else if (status == 2)
	{
		ft_error_directory(exec, data, 2);
		free(exec);
		return (NULL);
	}
	if (access(exec, X_OK) != 0)
	{
		access_error(data, &exec);
		return (NULL);
	}
	return (exec);
}

static int	directory_character(t_data *data, char *cmd)
{
	int	status;

	status = ft_check_file_type(cmd);
	if (status == 0)
	{
		ft_error_directory(cmd, data, 0);
		return (-1);
	}
	else if (status == 2)
	{
		ft_error_directory(cmd, data, 2);
		return (-1);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		data->status = 126;
		return (-1);
	}
	return (1);
}

static char	*get_path_util(char *cmd, char **envp, t_data *data, int i)
{
	char	**allpath;
	char	*exec;

	if (ft_check_set_unset(envp) == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		data->status = 127;
		return (NULL);
	}
	allpath = ft_split(ft_getenv("PATH", envp), ':');
	exec = ft_get_exec_path(cmd, allpath, i);
	ft_free_arr(allpath);
	if (exec)
		return (exec);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	data->status = 127;
	return (NULL);
}

char	*ft_get_path(char *cmd, char **envp, int i, t_data *data)
{
	if (!cmd)
		return (NULL);
	if (ft_strlen(cmd) < 1)
		return (ft_strdup(cmd));
	if (cmd[0] == '~')
		return (root_directory(data, cmd, envp));
	else if (is_directory_character(cmd))
	{
		if (directory_character(data, cmd) == -1)
			return (NULL);
		return (ft_strdup(cmd));
	}
	else
		return (get_path_util(cmd, envp, data, i));
}
