/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:57:12 by talin             #+#    #+#             */
/*   Updated: 2025/03/03 10:43:21 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_args(char *command, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	data->status = 1;
}

void	error_not_found(char *path, t_data *data)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	data->status = 1;
}

void	error_permission(char *command, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	data->status = 126;
}

void	error_directory(char *command, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	data->status = 126;
}

char	*get_path(t_data *data, char *variable)
{
	char	*path;

	path = env_value(data, variable);
	if (!path)
	{
		error_not_found(variable, data);
		return (NULL);
	}
	if (ft_strcmp(variable, "OLDPWD") == 0)
		ft_putendl_fd(path, STDOUT_FILENO);
	return (path);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_target(t_command *command, t_data *data)
{
	static char	target[4096];

	if (!command->args || !command->args[1])
		ft_strcpy(target, get_path(data, "HOME"));
	else if (ft_strcmp(command->args[1], "-") == 0)
		ft_strcpy(target, get_path(data, "OLDPWD"));
	else
		ft_strcpy(target, command->args[1]);
	return (target);
}

void	update_env(t_data *data, char *env_name, const char *new_value)
{
	t_envp	*temp;

	temp = data->envp;
	while (temp)
	{
		if (ft_strcmp(temp->key, env_name) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			temp->value = ft_strdup(new_value);
			if (!temp->value)
				return ;
			break ;
		}
		temp = temp->next;
	}
}

int	update_pwd(t_data *data, const char *old_pwd)
{
	char	new_pwd[4096];

	if (env_value(data, "OLDPWD"))
		update_env(data, "OLDPWD", old_pwd);
	if (!getcwd(new_pwd, 4096))
	{
		error_file_not_found("getcwd", data);
		return (1);
	}
	update_env(data, "PWD", new_pwd);
	return (0);
}

static int	chdir_error(char *dest_path, t_data *data)
{
	struct stat	path_stat;

	if (stat(dest_path, &path_stat) == -1)
	{
		if (access(dest_path, F_OK) == -1)
			error_not_found(dest_path, data);
		else
			error_permission(dest_path, data);
	}
	else
	{
		if (!S_ISDIR(path_stat.st_mode))
			error_directory(dest_path, data);
		else if (access(dest_path, X_OK) == -1)
			error_permission(dest_path, data);
	}
	return (1);
}

static int	validate_args(t_command *command, t_data *data)
{
	if (command->args && command->args[1] && command->args[2])
	{
		error_args("cd", data);
		return (0);
	}
	return (1);
}

static int	validate_path(char *dest_path, t_data *data)
{
	struct stat	path_stat;

	if (stat(dest_path, &path_stat) == -1)
	{
		if (access(dest_path, F_OK) == -1)
			error_not_found(dest_path, data);
		else
			error_permission(dest_path, data);
		return (0);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		error_directory(dest_path, data);
		return (0);
	}
	if (access(dest_path, X_OK) == -1)
	{
		error_permission(dest_path, data);
		return (0);
	}
	return (1);
}

static char	*get_destination_path(t_command *command, t_data *data)
{
	char	*dest_path;

	if (!validate_args(command, data))
		return (NULL);
	dest_path = get_target(command, data);
	if (!dest_path)
	{
		data->status = 1;
		return (NULL);
	}
	if (!validate_path(dest_path, data))
		return (NULL);
	return (dest_path);
}

int	ft_cd(t_command *command, t_data *data)
{
	char	*dest_path;
	char	old_path[4096];
	int		ret;

	if (!getcwd(old_path, 4096))
	{
		error_file_not_found("getcwd", data);
		return (1);
	}
	dest_path = get_destination_path(command, data);
	if (!dest_path)
		return (1);
	if (chdir(dest_path) == -1)
	{
		ret = chdir_error(dest_path, data);
		return (ret);
	}
	ret = update_pwd(data, old_path);
	return (ret);
}