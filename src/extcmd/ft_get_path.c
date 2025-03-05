/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:18:50 by talin             #+#    #+#             */
/*   Updated: 2025/03/05 13:52:12 by juhtoo-h         ###   ########.fr       */
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

char	*ft_get_path(char *cmd, char **envp, int i)
{
	char	*exec;
	char	**allpath;

	if (cmd[0] == '~')
		return (ft_get_home_path(cmd, envp));
	else
	{
		if (ft_check_set_unset(envp) == 0)
			return (ft_strdup(cmd));
		allpath = ft_split(ft_getenv("PATH", envp), ':');
		exec = ft_get_exec_path(cmd, allpath, i);
		ft_free_arr(allpath);
		if (exec)
			return (exec);
		return (ft_strdup(cmd));
	}
}
