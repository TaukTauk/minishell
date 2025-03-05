/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:36:35 by rick              #+#    #+#             */
/*   Updated: 2025/03/05 13:50:59 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->env[++i])
		printf("%s\n", data->env[i]);
	data->status = 0;
}

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf != NULL)
	{
		printf("%s\n", buf);
		free(buf);
	}
	else
		perror("getcwd");
}

int	execute_builtin(t_command *commands, t_data *data)
{
	if (ft_strcmp(commands->cmd, "env") == 0)
		return (ft_env(data), 1);
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
