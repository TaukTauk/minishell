/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:57:12 by talin             #+#    #+#             */
/*   Updated: 2025/03/12 14:47:04 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
