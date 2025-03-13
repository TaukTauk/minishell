/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:18:50 by talin             #+#    #+#             */
/*   Updated: 2025/03/13 15:21:48 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_get_home_path(char *cmd, char **envp)
{
	char	*path_part;
	char	*home;

	home = ft_getenv("HOME", envp);
	if (!home)
		return (ft_strdup(cmd));
	path_part = ft_strjoin(home, cmd + 1);
	return (path_part);
}

static char	*ft_get_exec_path(char *cmd, char **allpath, int i)
{
	char	*path_part;
	char	*exec;

	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	return (NULL);
}

int	ft_check_file_type(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (2);
	if (S_ISDIR(path_stat.st_mode))
		return (0);
	return (1);
}

void	ft_error_directory(char *exec, t_data *data, int status)
{
	if (status == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		data->status = 126;
	}
	else if (status == 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		data->status = 127;
	}
}

int	is_directory_character(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.' || cmd[ft_strlen(cmd) - 1] == '/')
		return (1);
	return (0);
}

char *ft_get_path(char *cmd, char **envp, int i, t_data *data)
{
    char *exec;
    char **allpath;
    int status;

    if (!cmd)
        return (NULL);
    if (cmd[0] == '~')
    {
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
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(exec, STDERR_FILENO);
            ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
            data->status = 126;
            free(exec);
            return (NULL);
        }
        return (exec);
    }
    else if (is_directory_character(cmd))
    {
        status = ft_check_file_type(cmd);
        if (status == 0)
        {
            ft_error_directory(cmd, data, 0);
            return (NULL);
        }
        else if (status == 2)
        {
            ft_error_directory(cmd, data, 2);
            return (NULL);
        }
        if (access(cmd, X_OK) != 0)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(cmd, STDERR_FILENO);
            ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
            data->status = 126;
            return (NULL);
        }
        return (ft_strdup(cmd));
    }
    else
    {
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
}
