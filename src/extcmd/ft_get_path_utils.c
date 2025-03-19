/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:35:28 by juhtoo-h          #+#    #+#             */
/*   Updated: 2025/03/17 15:12:43 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_home_path(char *cmd, char **envp)
{
	char	*path_part;
	char	*home;

	home = ft_getenv("HOME", envp);
	if (!home)
		return (ft_strdup(cmd));
	path_part = ft_strjoin(home, cmd + 1);
	return (path_part);
}

char	*ft_get_exec_path(char *cmd, char **allpath, int i)
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
