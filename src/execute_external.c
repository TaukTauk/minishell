/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:37:48 by rick              #+#    #+#             */
/*   Updated: 2025/02/28 09:39:11 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

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

char	*ft_get_path(char *cmd, char **envp, int i)
{
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	*home;

	if (cmd[0] == '~')
	{
		home = ft_getenv("HOME", envp);
		if (!home)
			return (cmd);
		path_part = ft_strjoin(home, cmd + 1);
		return (path_part); 
	}
	else
	{
		if (ft_check_set_unset(envp) == 0)
			return (cmd);
		allpath = ft_split(ft_getenv("PATH", envp), ':');
		while (allpath[++i])
		{
			path_part = ft_strjoin(allpath[i], "/");
			exec = ft_strjoin(path_part, cmd);
			free(path_part);
			if (access(exec, F_OK | X_OK) == 0)
			{
				ft_free_arr(allpath);
				return (exec);
			}
			free(exec);
		}
		ft_free_arr(allpath);
		return (cmd);
	}
}

void	execve_cmd(char *cmd, char **s_cmd, char **envp)
{
	char *path;

	path = ft_get_path(cmd, envp, -1);
	if (execve(path, s_cmd, envp) == -1)
	{
		if (access(path, F_OK) == 0)
			ft_putstr_fd("permission denied: ", 2);
		else
			ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
	}
}