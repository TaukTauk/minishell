/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:33:06 by rick              #+#    #+#             */
/*   Updated: 2025/03/12 14:46:19 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (!src)
		return (NULL);
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

static void	update_env(t_data *data, char *env_name, const char *new_value)
{
	t_envp	*temp;

	temp = data->envp;
	while (temp)
	{
		if (ft_strcmp(temp->key, env_name) == 0)
		{
			if (temp->value)
			{
				free(temp->value);
				temp->value = NULL;
			}
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
