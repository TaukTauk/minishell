/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:22:58 by talin             #+#    #+#             */
/*   Updated: 2025/01/23 16:02:17 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_commands(t_data *data)
{
	int	i;

	if (data->commands->cmd)
	{
		if (ft_strcmp(data->commands->cmd, "env") == 0)
		{
			i = -1;
			while (data->env[++i])
			{
				printf("%s\n", data->env[i]);
			}
		}
		else if (ft_strcmp(data->commands->cmd, "echo") == 0)
		{
			i = 0;
			while (data->commands->args[++i])
			{
				printf("%s", data->commands->args[i]);
			}
			printf("\n");
		}
		else if (ft_strcmp(data->commands->cmd, "cd") == 0)
		{
			if (data->commands->args[1])
			{
				if (chdir(data->commands->args[1]) != 0)
				perror("chdir() failed");
			}
			else
			{
				char	*home;

				i = -1;
				home = NULL;
				while (data->env[++i])
				{
					if (ft_strncmp("HOME=", data->env[i], 5) == 0)
					{
						home = ft_strdup(data->env[i] + 5);
						break ;
					}
				}
				if (home)
				{
					if (chdir(home) != 0)
					perror("chdir() failed");
				}
				
			}
		}
		else if (ft_strcmp(data->commands->cmd, "pwd") == 0)
		{
			char *buf;
			buf = getcwd(NULL, 0);
			if (buf != NULL) {
				printf("%s\n", buf);
				free(buf);
			} else {
				perror("getcwd");
			}
		}
		else if (ft_strcmp(data->commands->cmd, "export") == 0)
		{}
		else if (ft_strcmp(data->commands->cmd, "unset") == 0)
		{}
		else if (ft_strcmp(data->commands->cmd, "exit") == 0)
		{
			return (0);
		}
		else
		{
			execve(data->commands->cmd, data->commands->args, data->env);
		}
	}
	return (1);
}
